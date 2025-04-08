#include "bn_log.h"
#include "battle.h"
#include "card_ids.h"

Battle::Battle() {
	init_decks();
	draw_starting_hands();
	m_opponent_hand.set_visible(false);
}

void Battle::init_decks() {
	load_deck_id(DeckId::DECK_OVERGROWTH, m_player_deck);
	load_deck_id(DeckId::DECK_ZAP, m_opponent_deck);
	shuffle_deck(m_player_deck);
	shuffle_deck(m_opponent_deck);
}

void Battle::draw_starting_hands() {
	for(int i = 0; i < 7; i++) {
		BN_LOG("Drawing card. . .");
		draw_card(m_player_deck, m_player_hand);
		draw_card(m_opponent_deck, m_opponent_hand);
	}
}

void Battle::update() {
	m_field.update();
	m_player_hand.update();
	m_opponent_hand.update();
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

void Battle::end_turn() {
	m_turn_player = (m_turn_player == TurnPlayer::PLAYER) ? TurnPlayer::OPPONENT : TurnPlayer::PLAYER;
}

Phase Battle::current_phase() const {
	return m_phase;
}

void Battle::reset_phase() {
	m_phase = Phase::DRAW;
}

void Battle::next_phase() {
	switch(m_phase) {
		case Phase::DRAW:
			m_phase = Phase::MAIN;
			break;
		case Phase::MAIN:
			m_phase = Phase::BATTLE;
			break;
		case Phase::BATTLE:
			m_phase = Phase::END;
			break;
		case Phase::END:
			end_turn();
			reset_phase();
			break;
		default:
			return;
	}
}

bool Battle::is_phase(Phase phase) const {
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