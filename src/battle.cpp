#include "bn_keypad.h"
#include "battle.h"
#include "card_ids.h"

Battle::Battle() {
	init_decks();
	m_state = BattleState::COIN_FLIP;
}

void Battle::init_decks() {
	load_deck_id(DeckId::DECK_OVERGROWTH, m_player_deck);
	load_deck_id(DeckId::DECK_ZAP, m_opponent_deck);
	shuffle_deck(m_player_deck);
	shuffle_deck(m_opponent_deck);
}

void Battle::draw_starting_hands() {
	for(int i = 0; i < 7; i++) {
		draw_card(m_player_deck, m_player_hand);
		draw_card(m_opponent_deck, m_opponent_hand);
	}
	
	m_opponent_hand.set_visible(false);
}

void Battle::update() {
	switch(m_state) {
		case BattleState::COIN_FLIP:
			update_coin_flip();
			return;
		case BattleState::SETUP_HANDS:
			update_setup_hands();
			break;
		case BattleState::SETUP_ACTIVE:
			update_setup_active();
			break;
		case BattleState::SETUP_BENCH:
			update_setup_bench();
			break;
		case BattleState::SETUP_PRIZES:
			update_setup_prizes();
			break;
		case BattleState::READY_TO_START:
			start_turn();
			break;
		case BattleState::PLAYER_TURN:
			update_player_turn();
			break;
		case BattleState::OPPONENT_TURN:
			update_opponent_turn();
			break;
		case BattleState::CHECK_WIN:
			check_win_conditions();
			break;
	}
	
	m_field.update();
	m_player_hand.update();
	m_opponent_hand.update();
}

void Battle::update_coin_flip() {
	// TODO: Implement coin flipping + first turn player determination
	if(!m_coin_flipping) {
		m_flipper.start_flip();
		m_coin_flipping = true;
	}
	
	m_flipper.update();
	
	if(m_flipper.done()) {
		m_turn_player = (m_flipper.result() == CoinResult::HEADS) ? TurnPlayer::PLAYER : TurnPlayer::OPPONENT;
		m_flipper.destroy();
		m_state = BattleState::SETUP_HANDS;
	}
}

void Battle::update_setup_hands() {
	draw_starting_hands();
	// TODO: Implement mulligans
	m_state = BattleState::SETUP_ACTIVE;
}

void Battle::update_setup_active() {
	// TODO: Implement putting Pokemon in the active spot
	m_state = BattleState::SETUP_BENCH;
}

void Battle::update_setup_bench() {
	// TODO: Implement putting Pokemon on the bench
	m_state = BattleState::SETUP_PRIZES;
}

void Battle::update_setup_prizes() {
	// TODO: Implement prize cards
	m_state = BattleState::READY_TO_START;
}

void Battle::start_turn() {
	reset_phase();
	m_state = (m_turn_player == TurnPlayer::PLAYER) ? BattleState::PLAYER_TURN : BattleState::OPPONENT_TURN;
}

void Battle::update_player_turn() {
	update_phase();
	m_state = BattleState::OPPONENT_TURN;
}

void Battle::update_opponent_turn() {
	update_phase();
	m_state = BattleState::PLAYER_TURN;
}

void Battle::check_win_conditions() {
	// TODO: Implement win conditions
}

void Battle::update_phase() {
	switch(m_phase) {
		case TurnPhase::DRAW:
			switch(m_turn_player) {
				case TurnPlayer::PLAYER:
					m_opponent_hand.set_visible(false);
					m_field.scroll_to_player();
					m_player_hand.set_visible(true);
					try_draw_card_player();
					break;
				case TurnPlayer::OPPONENT:
					m_player_hand.set_visible(false);
					m_field.scroll_to_opponent();
					m_opponent_hand.set_visible(true);
					try_draw_card_opponent();
					break;
			}
			
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
			m_turn_player = (m_turn_player == TurnPlayer::PLAYER) ? TurnPlayer::OPPONENT : TurnPlayer::PLAYER;
			reset_phase();
			break;
	}
}

Field& Battle::field() {
	return m_field;
}

const Field& Battle::field() const {
	return m_field;
}

TurnPlayer Battle::current_turn() const {
	return m_turn_player;
}

bool Battle::is_player_turn() const {
	return m_turn_player == TurnPlayer::PLAYER;
}

bool Battle::is_opponent_turn() const {
	return m_turn_player == TurnPlayer::OPPONENT;
}

TurnPhase Battle::current_phase() const {
	return m_phase;
}

void Battle::reset_phase() {
	m_phase = TurnPhase::DRAW;
}

bool Battle::is_phase(TurnPhase phase) const {
	return m_phase == phase;
}

void Battle::try_draw_card_player() {
	if(!m_player_deck.empty() && m_player_hand.card_count() < 10) {
		draw_card(m_player_deck, m_player_hand);
	}
}

void Battle::try_draw_card_opponent() {
	if(!m_opponent_deck.empty() && m_opponent_hand.card_count() < 10) {
		draw_card(m_opponent_deck, m_opponent_hand);
	}
}

Hand Battle::player_hand() const {
	return m_player_hand;
}

Hand Battle::opponent_hand() const {
	return m_opponent_hand;
}