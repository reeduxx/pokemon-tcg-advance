#include "bn_keypad.h"
#include "battle_engine.h"
#include "card_ids.h"
#include "cards.h"

BattleEngine::BattleEngine(Cursor& cursor, Hand& player_hand, Hand& opponent_hand, Field& field) : m_cursor(cursor), m_player_hand(player_hand), m_opponent_hand(opponent_hand), m_field(field) {
	init_decks();
	m_state = BattleState::COIN_FLIP;
}

void BattleEngine::init_decks() {
	load_deck_id(DeckId::DECK_OVERGROWTH, m_player_deck);
	load_deck_id(DeckId::DECK_ZAP, m_opponent_deck);
	shuffle_deck(m_player_deck);
	shuffle_deck(m_opponent_deck);
}


void BattleEngine::update() {
	switch(m_state) {
		case BattleState::COIN_FLIP:
			task_coin_flip();
			return;
		case BattleState::SETUP_HANDS:
			task_setup_hands();
			break;
		case BattleState::SETUP_ACTIVE:
			task_setup_active();
			break;
		case BattleState::SETUP_BENCH:
			task_setup_bench();
			break;
		case BattleState::SETUP_PRIZES:
			task_setup_prizes();
			break;
		case BattleState::BATTLE_START:
			task_start_turn();
			break;
		case BattleState::PLAYER_TURN:
			task_player_turn();
			break;
		case BattleState::OPPONENT_TURN:
			task_opponent_turn();
			break;
		case BattleState::CHECK_WIN:
			task_check_win_conditions();
			break;
		default:
			break;
	}
}

void BattleEngine::task_coin_flip() {
	if(!m_coin_flipping) {
		m_coin_flipper.start_flip();
		m_coin_flipping = true;
	}
	
	if(m_coin_flipper.done()) {
		m_turn_player = (m_coin_flipper.result() == CoinResult::HEADS) ? TurnPlayer::PLAYER : TurnPlayer::OPPONENT;
		
		if(bn::keypad::a_pressed()) {
			m_coin_flipper.destroy();
			m_state = BattleState::SETUP_HANDS;
		}
	} else {
		m_coin_flipper.update();
	}
}

void BattleEngine::task_setup_hands() {
	// TODO: Implement mulligans
	m_field.scroll_to_player();
	m_state = BattleState::SETUP_ACTIVE;
}

void BattleEngine::task_setup_active() {
	if(bn::keypad::a_pressed()) {
		int i = m_cursor.hand_idx();

		if(i >= 0 && i < m_player_hand.card_count()) {
			BattleCard card = m_player_hand.get_card(i);

			if(is_basic_pokemon(card)) {
				m_field.place_card(ZoneId::PLAYER_ACTIVE, card);
				m_player_hand.remove_card(i);
				m_cursor.set_hand_idx(0);
				m_state = BattleState::SETUP_BENCH;
			}
		}
	}
}

void BattleEngine::task_setup_bench() {
	static int bench_i = 0;

	if(bn::keypad::a_pressed()) {
		int i = m_cursor.hand_idx();

		if(i >= 0 && i < m_player_hand.card_count()) {
			BattleCard card = m_player_hand.get_card(i);

			if(is_basic_pokemon(card) && bench_i < 5) {
				ZoneId zone = static_cast<ZoneId>(static_cast<int>(ZoneId::PLAYER_BENCH_1) + bench_i);
				m_field.place_card(zone, card);
				m_player_hand.remove_card(i);
				m_cursor.set_hand_idx(0);
				bench_i++;
			}
		}
	}

	if(bench_i >= 5 || bn::keypad::start_pressed()) {
		bench_i = 0;
		m_state = BattleState::SETUP_PRIZES;
	}
}

void BattleEngine::task_setup_prizes() {
	// TODO: Implement prize cards
	m_state = BattleState::BATTLE_START;
}

void BattleEngine::task_start_turn() {
	reset_phase();
	m_state = (m_turn_player == TurnPlayer::PLAYER) ? BattleState::PLAYER_TURN : BattleState::OPPONENT_TURN;
}

void BattleEngine::task_player_turn() {
	update_phase();
	if(is_phase(TurnPhase::END))
		m_state = BattleState::OPPONENT_TURN;
}

void BattleEngine::task_opponent_turn() {
	update_phase();
	if(is_phase(TurnPhase::END))
		m_state = BattleState::PLAYER_TURN;
}

void BattleEngine::task_check_win_conditions() {
	// TODO: Implement win conditions
}

void BattleEngine::update_phase() {
	switch(m_phase) {
		case TurnPhase::DRAW:
			switch(m_turn_player) {
				case TurnPlayer::PLAYER:
					m_opponent_hand.set_visible(false);
					m_field.scroll_to_player();
					m_player_hand.set_visible(true);
					break;
				case TurnPlayer::OPPONENT:
					m_player_hand.set_visible(false);
					m_field.scroll_to_opponent();
					m_opponent_hand.set_visible(true);
					break;
				default:
					break;
			}
			
			draw_turn_card();
			m_phase = TurnPhase::MAIN;
			break;
		case TurnPhase::MAIN:
			if(bn::keypad::start_pressed())
				m_phase = TurnPhase::BATTLE;
			break;
		case TurnPhase::BATTLE:
			m_phase = TurnPhase::END;
			break;
		case TurnPhase::END:
			reset_phase();
			m_turn_player = (m_turn_player == TurnPlayer::PLAYER) ? TurnPlayer::OPPONENT : TurnPlayer::PLAYER;
			break;
		default:
			break;
	}
}

Field& BattleEngine::field() {
	return m_field;
}

const Field& BattleEngine::field() const {
	return m_field;
}

TurnPlayer BattleEngine::current_turn() const {
	return m_turn_player;
}

bool BattleEngine::is_player_turn() const {
	return m_turn_player == TurnPlayer::PLAYER;
}

bool BattleEngine::is_opponent_turn() const {
	return m_turn_player == TurnPlayer::OPPONENT;
}

TurnPhase BattleEngine::current_phase() const {
	return m_phase;
}

void BattleEngine::reset_phase() {
	m_phase = TurnPhase::DRAW;
}

bool BattleEngine::is_phase(TurnPhase phase) const {
	return m_phase == phase;
}

Hand BattleEngine::player_hand() const {
	return m_player_hand;
}

Hand BattleEngine::opponent_hand() const {
	return m_opponent_hand;
}

BattleState BattleEngine::current_state() const {
	return m_state;
}

bool BattleEngine::is_basic_pokemon(const BattleCard& card) const {
	const Card* data = get_card_by_id(card.card_id);
	return data && data->header.type == CardType::CARD_POKEMON && (data->pokemon.stage == 0 || data->pokemon.stage == 1);
}

bool BattleEngine::can_draw(TurnPlayer turn_player) const {
	switch(turn_player) {
		case TurnPlayer::PLAYER:
			return !m_player_deck.empty() && m_player_hand.card_count() < 10;
		case TurnPlayer::OPPONENT:
			return !m_opponent_deck.empty() && m_opponent_hand.card_count() < 10;
		default:
			return false;
	}
}

BattleCard BattleEngine::draw_card(TurnPlayer turn_player) {
	switch(turn_player) {
		case TurnPlayer::PLAYER: {
			BattleCard card = m_player_deck.back();
			m_player_deck.pop_back();
			return card;
		}
		case TurnPlayer::OPPONENT: {
			BattleCard card = m_opponent_deck.back();
			m_opponent_deck.pop_back();
			return card;
		}
		default:
			return BattleCard();
	}
}

void BattleEngine::draw_turn_card() {
	if(can_draw(m_turn_player)) {
		BattleCard card = draw_card(m_turn_player);

		if(is_player_turn()) {
			m_player_hand.add_card(card);
		} else {
			m_opponent_hand.add_card(card);
		}
	}
}