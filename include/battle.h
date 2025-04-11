#ifndef GUARD_BATTLE_H
#define GUARD_BATTLE_H

#include "coin_flipper.h"
#include "deck.h"
#include "field.h"
#include "hand.h"

enum TurnPlayer {
	PLAYER,
	OPPONENT
};

enum class BattleState {
	COIN_FLIP,
	SETUP_HANDS,
	SETUP_ACTIVE,
	SETUP_BENCH,
	SETUP_PRIZES,
	READY_TO_START,
	PLAYER_TURN,
	OPPONENT_TURN,
	CHECK_WIN
};

enum class TurnPhase {
	DRAW,
	MAIN,
	BATTLE,
	END
};

class Battle {
	private:
		Deck m_player_deck;
		Deck m_opponent_deck;
		CoinFlipper m_flipper;
		bool m_coin_flipping = false;
		Hand m_player_hand{false};
		Hand m_opponent_hand{true};
		Field m_field;
		TurnPlayer m_turn_player;
		BattleState m_state;
		TurnPhase m_phase;
	public:
		Battle();
		void update();
		Field& field();
		const Field& field() const;
		TurnPlayer current_turn() const;
		bool is_player_turn() const;
		bool is_opponent_turn() const;
		TurnPhase current_phase() const;
		void reset_phase();
		bool is_phase(TurnPhase phase) const;
		void try_draw_card_player();
		void try_draw_card_opponent();
		Hand player_hand() const;
		Hand opponent_hand() const;
	private:
		void init_decks();
		void draw_starting_hands();
		void update_coin_flip();
		void update_setup_hands();
		void update_setup_active();
		void update_setup_bench();
		void update_setup_prizes();
		void start_turn();
		void update_player_turn();
		void update_opponent_turn();
		void check_win_conditions();
		void update_phase();
};

#endif // GUARD_BATTLE_H