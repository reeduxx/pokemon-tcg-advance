#include "cursor_controller.h"

CursorController::CursorController(Cursor& cursor, Battle& battle) : m_cursor(cursor), m_battle(battle) {
	snap(BENCH_START);
}

void CursorController::snap(int i) {
	m_cursor.set_zone_idx(i);
	m_cursor.snap_to(m_battle.field().get_zone(i).m_pos);
}

void CursorController::update() {
	int i = m_cursor.zone_idx();
	if(bn::keypad::a_pressed()) {
		m_battle.try_draw_card_player();
	}
	
	if(bn::keypad::left_pressed()) {
		if(i >= BENCH_START && i <= BENCH_END) {
			snap(i == BENCH_START ? BENCH_END : i - 1);
		} else if(i >= OPP_BENCH_START && i <= OPP_BENCH_END) {
			snap(i == OPP_BENCH_START ? OPP_BENCH_END : i - 1);
		}else if(i == ACTIVE || i == OPP_ACTIVE) {
			snap(STADIUM);
		}
	} else if(bn::keypad::right_pressed()) {
		if(i >= BENCH_START && i <= BENCH_END) {
			snap(i == BENCH_END ? BENCH_START : i + 1);
		} else if(i >= OPP_BENCH_START && i <= OPP_BENCH_END) {
			snap(i == OPP_BENCH_END ? OPP_BENCH_START : i + 1);
		}else if(i == STADIUM) {
			i = ACTIVE;
			m_battle.field().scroll_to_player();
			snap(ACTIVE);
		}
	} else if(bn::keypad::up_pressed()) {
		if(i >= BENCH_START && i <= BENCH_END) {
			snap(ACTIVE);
		} else if(i == ACTIVE) {
			m_battle.field().scroll_to_opponent();
			snap(OPP_ACTIVE);
		} else if(i == OPP_ACTIVE) {
			snap(OPP_BENCH_START);
		}
	} else if(bn::keypad::down_pressed()) {
		if(i == ACTIVE) {
			snap(BENCH_START);
		} else if(i >= OPP_BENCH_START && i <= OPP_BENCH_END) {
			snap(OPP_ACTIVE);
		}else if(i == OPP_ACTIVE) {
			m_battle.field().scroll_to_player();
			snap(ACTIVE);
		}
	}
}