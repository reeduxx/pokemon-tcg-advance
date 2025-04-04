#ifndef GUARD_BATTLE_H
#define GUARD_BATTLE_H

#include "deck.h"
#include "field.h"
#include "hand.h"

enum TurnPlayer {
	PLAYER,
	OPPONENT
};

enum class Phase {
	DRAW,
	MAIN,
	BATTLE,
	END
};

class Battle {
	private:
		Deck m_player_deck;
		Deck m_opponent_deck;
		Hand m_player_hand;
		Hand m_opponent_hand;
		Field m_field;
		TurnPlayer m_turn_player = TurnPlayer::PLAYER;
		Phase m_phase = Phase::DRAW;
	public:
		Battle();
		void update();
		Field& field();
		const Field& field() const;
		TurnPlayer current_turn() const;
		void end_turn();
		bool is_player_turn() const;
		bool is_opponent_turn() const;
		Phase current_phase() const;
		void next_phase();
		void reset_phase();
		bool is_phase(Phase phase) const;
		void try_draw_card_player();
		void try_draw_card_opponent();
	private:
		void init_decks();
		void draw_starting_hands();
};

#endif // GUARD_BATTLE_H