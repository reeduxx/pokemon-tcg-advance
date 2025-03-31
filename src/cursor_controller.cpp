#include "cursor_controller.h"

CursorController::CursorController(Cursor& cursor, Playmat& playmat) : m_cursor(cursor), m_playmat(playmat) {
	snap(BENCH_START);
}

void CursorController::snap(int i) {
	m_cursor.set_zone_idx(i);
	m_cursor.snap_to(m_playmat.get_zone(i).pos);
}

void CursorController::update() {
	int i = m_cursor.zone_idx();
	
	if(bn::keypad::left_pressed()) {
		/*if(i >= HAND_START && i <= HAND_END) {
			snap(i == HAND_START ? HAND_END : i - 1);
		} else*/if(i >= BENCH_START && i <= BENCH_END) {
			snap(i == BENCH_START ? BENCH_END : i - 1);
		} else if(i == ACTIVE || i == OPP_ACTIVE) {
			snap(STADIUM);
		}
	} else if(bn::keypad::right_pressed()) {
		/*if(i >= HAND_START && i <= HAND_END) {
			snap(i == HAND_END ? HAND_START : i + 1);
		} else*/if(i >= BENCH_START && i <= BENCH_END) {
			snap(i == BENCH_END ? BENCH_START : i + 1);
		} else if(i == STADIUM) {
			snap(ACTIVE);
		}
	} else if(bn::keypad::up_pressed()) {
		/*if(i >= HAND_START && i <= HAND_END) {
			if(BENCH_START <= BENCH_END) {
				snap(BENCH_START);
			} else {
				snap(ACTIVE);
			}
		} else*/if(i >= BENCH_START && i <= BENCH_END) {
			snap(ACTIVE);
		} else if(i == ACTIVE) {
			snap(OPP_ACTIVE);
		} else if(i == OPP_ACTIVE) {
			snap(OPP_BENCH_START);
		}
	} else if(bn::keypad::down_pressed()) {
		/*if(i >= BENCH_START && i <= BENCH_END) {
			snap(HAND_START);
		} else*/if(i == ACTIVE) {
			snap(BENCH_START);
		} else if(i == OPP_ACTIVE) {
			snap(ACTIVE);
		}
	}
	
	if(i >= OPP_BENCH_START) {
		m_playmat.scroll_to_opponent();
	} else {
		m_playmat.scroll_to_player();
	}
}