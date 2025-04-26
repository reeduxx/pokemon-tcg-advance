#ifndef GUARD_BATTLE_ENGINE_H
#define GUARD_BATTLE_ENGINE_H

#include "coin_flipper.h"
#include "battle_cursor.h"
#include "deck.h"
#include "field.h"
#include "hand.h"

/**
 * @brief Enum representing whose turn it is.
 */
enum TurnPlayer {
	PLAYER,
	OPPONENT
};

/**
 * @brief Enum representing the state of the battle.
 */
enum class BattleState {
	COIN_FLIP,
	DRAW_HANDS,
	MULLIGAN,
	MULLIGAN_PLAYER_DRAW,
	MULLIGAN_OPPONENT_DRAW,
	SETUP_ACTIVE,
	SETUP_BENCH,
	SETUP_PRIZES,
	BATTLE_START,
	PLAYER_TURN,
	OPPONENT_TURN,
	CHECK_WIN
};

/**
 * @brief Enum representing the phase of the turn.
 */
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
		BattleCursor& m_cursor;
		Deck m_player_deck;
		Deck m_opponent_deck;
		Hand& m_player_hand, & m_opponent_hand;
		Field& m_field;
		TurnPhase m_phase;
		TurnPlayer m_turn_player;
		bool m_coin_flipping = false;
		int m_player_mulligans = 0, m_opponent_mulligans = 0;
	public:
		BattleEngine(BattleCursor& cursor, Hand& player_hand, Hand& opponent_hand, Field& field);
		void update();
		Field& field();
		const Field& field() const;
		TurnPlayer current_turn() const;
		bool is_player_turn() const;
		bool is_opponent_turn() const;
		TurnPhase current_phase() const;
		void reset_phase();
		bool is_phase(TurnPhase phase) const;
		Hand player_hand() const;
		Hand opponent_hand() const;
		BattleState current_state() const;
		bool can_draw(TurnPlayer turn_player) const;
		BattleCard draw_card(TurnPlayer turn_player);
		void draw_hand(TurnPlayer turn_player);
		void try_draw_card(TurnPlayer turn_player);
		bool can_evolve(const BattleCard& from, const BattleCard& to) const;
		void evolve(BattleCard& evolution, ZoneId zone_id);
	private:
		void init_decks();
		void task_coin_flip();
		void task_draw_hands();
		void task_mulligan();
		void task_mulligan_player_draw();
		void task_mulligan_opponent_draw();
		void task_setup_active();
		void task_setup_bench();
		void task_setup_prizes();
		void task_start_turn();
		void task_player_turn();
		void task_opponent_turn();
		void task_check_win_conditions();
		void update_phase();
		bool is_basic_pokemon(const BattleCard& card) const;
		bool has_basic(const Hand& hand) const;
};

#endif // GUARD_BATTLE_H