#include "bn_keypad.h"
#include "bn_log.h"
#include "card_names.h"
#include "cards.h"
#include "cursor_controller.h"
#include "zone.h"

CursorController::CursorController(Cursor& cursor, Battle& battle) : m_cursor(cursor), m_battle(battle) {
	m_cursor.set_hand_idx(0);
	m_cursor.set_pos(m_battle.player_hand().get_card_pos(0));
}

void CursorController::update() {
	if(m_battle.current_state() == BattleState::COIN_FLIP || m_battle.current_state() == BattleState::OPPONENT_TURN) {
		m_cursor.set_visible(false);
	} else {
		m_cursor.set_visible(true);
	}
	
	ZoneId zone = m_cursor.zone();
	
	if(m_cursor.mode() == CursorMode::HAND && m_cursor.position() != m_battle.player_hand().get_card_pos(m_cursor.hand_idx())) {
		m_cursor.set_pos(m_battle.player_hand().get_card_pos(m_cursor.hand_idx()));
	}
	
	// Left
	if(bn::keypad::left_pressed()) {
		if(m_cursor.mode() == CursorMode::HAND) {
			if(m_cursor.hand_idx() > 0) {
				int i = m_cursor.hand_idx() - 1;
				m_cursor.set_hand_idx(i);
				m_cursor.set_pos(m_battle.player_hand().get_card_pos(i));
			}
		} else if(zone >= ZoneId::PLAYER_BENCH_1 && zone <= ZoneId::PLAYER_BENCH_5) {
			snap_to_zone(zone == ZoneId::PLAYER_BENCH_1 ? ZoneId::PLAYER_BENCH_5 : static_cast<ZoneId>(static_cast<int>(zone) - 1));
		} else if(zone >= ZoneId::OPPONENT_BENCH_1 && zone <= ZoneId::OPPONENT_BENCH_5) {
			snap_to_zone(zone == ZoneId::OPPONENT_BENCH_1 ? ZoneId::OPPONENT_BENCH_5 : static_cast<ZoneId>(static_cast<int>(zone) - 1));
		} else if(zone == ZoneId::PLAYER_ACTIVE || zone == ZoneId::OPPONENT_ACTIVE) {
			snap_to_zone(ZoneId::STADIUM, m_battle.field().side());
		}
	}
	// Right
	if(bn::keypad::right_pressed()) {
		if(m_cursor.mode() == CursorMode::HAND) {
			if(m_cursor.hand_idx() < m_battle.player_hand().card_count() - 1) {
				int i = m_cursor.hand_idx() + 1;
				m_cursor.set_hand_idx(i);
				m_cursor.set_pos(m_battle.player_hand().get_card_pos(i));
			}
		} else if(zone >= ZoneId::PLAYER_BENCH_1 && zone <= ZoneId::PLAYER_BENCH_5) {
			snap_to_zone(zone == ZoneId::PLAYER_BENCH_5 ? ZoneId::PLAYER_BENCH_1 : static_cast<ZoneId>(static_cast<int>(zone) + 1));
		} else if(zone >= ZoneId::OPPONENT_BENCH_1 && zone <= ZoneId::OPPONENT_BENCH_5) {
			snap_to_zone(zone == ZoneId::OPPONENT_BENCH_5 ? ZoneId::OPPONENT_BENCH_1 : static_cast<ZoneId>(static_cast<int>(zone) + 1));
		} else if(zone == ZoneId::STADIUM) {
			if(m_battle.field().side() == Side::SIDE_PLAYER) {
				snap_to_zone(ZoneId::PLAYER_ACTIVE);
			}
			if(m_battle.field().side() == Side::SIDE_OPPONENT) {
				snap_to_zone(ZoneId::OPPONENT_ACTIVE);
			}
		}
	}
	// Up
	if(bn::keypad::up_pressed() && m_battle.current_state() >= BattleState::BATTLE_START) {
		if(m_cursor.mode() == CursorMode::HAND) {
			m_cursor.set_mode(CursorMode::FIELD);
			snap_to_zone(ZoneId::PLAYER_BENCH_1);
		} else if(zone >= ZoneId::PLAYER_BENCH_1 && zone <= ZoneId::PLAYER_BENCH_5) {
			snap_to_zone(ZoneId::PLAYER_ACTIVE);
		} else if(zone == ZoneId::PLAYER_ACTIVE) {
			m_battle.field().scroll_to_opponent();
			m_battle.opponent_hand().set_visible(true);
			m_battle.player_hand().set_visible(false);
			snap_to_zone(ZoneId::OPPONENT_ACTIVE);
		} else if(zone == ZoneId::OPPONENT_ACTIVE) {
			snap_to_zone(ZoneId::OPPONENT_BENCH_1);
		}
	}
	// Down
	if(bn::keypad::down_pressed() && m_battle.current_state() >= BattleState::BATTLE_START) {
		if(zone == ZoneId::PLAYER_ACTIVE) {
			snap_to_zone(ZoneId::PLAYER_BENCH_1);
		} else if(zone >= ZoneId::PLAYER_BENCH_1 && zone <= ZoneId::PLAYER_BENCH_5 && m_cursor.mode() != CursorMode::HAND) {
			if(m_battle.player_hand().card_count() > 0) {
				m_cursor.set_mode(CursorMode::HAND);
				m_cursor.set_hand_idx(0);
				bn::fixed_point pos = m_battle.player_hand().get_card_pos(0);
				m_cursor.set_pos(pos);
			}
		} else if(zone >= ZoneId::OPPONENT_BENCH_1 && zone <= ZoneId::OPPONENT_BENCH_5) {
			snap_to_zone(ZoneId::OPPONENT_ACTIVE);
		} else if(zone == ZoneId::OPPONENT_ACTIVE) {
			m_battle.field().scroll_to_player();
			m_battle.opponent_hand().set_visible(false);
			m_battle.player_hand().set_visible(true);
			snap_to_zone(ZoneId::PLAYER_ACTIVE);
		}
	}
}

void CursorController::snap_to_zone(ZoneId id, Side side) {
	m_cursor.set_zone(id);
	
	if(side == Side::SIDE_OPPONENT) {
		m_cursor.set_pos(m_battle.field().get_zone(id).m_opponent_pos);
	} else {
		m_cursor.set_pos(m_battle.field().get_zone(id).m_pos);
	}
}
