#ifndef GUARD_BATTLE_ENGINE_H
#define GUARD_BATTLE_ENGINE_H

#include "coin_flipper.h"
#include "cursor.h"
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
	BATTLE_START,
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

class BattleEngine {
	private:
		BattleState m_state;
		CoinFlipper m_coin_flipper;
		Cursor& m_cursor;
		Deck m_player_deck;
		Deck m_opponent_deck;
		Field& m_field;
		Hand& m_player_hand;
		Hand& m_opponent_hand;
		TurnPhase m_phase;
		TurnPlayer m_turn_player;
		bool m_coin_flipping = false;
	public:
		BattleEngine(Cursor& cursor, Hand& player_hand, Hand& opponent_hand, Field& field);
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
		BattleState current_state() const;
	private:
		void init_decks();
		void draw_starting_hands();
		void task_coin_flip();
		void task_setup_hands();
		void task_setup_active();
		void task_setup_bench();
		void task_setup_prizes();
		void task_start_turn();
		void task_player_turn();
		void task_opponent_turn();
		void task_check_win_conditions();
		void update_phase();
		bool is_basic_pokemon(const BattleCard& card) const;
};

#endif // GUARD_BATTLE_H