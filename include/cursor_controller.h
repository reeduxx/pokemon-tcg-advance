#ifndef GUARD_CURSOR_CONTROLLER_H
#define GUARD_CURSOR_CONTROLLER_H

#include "bn_keypad.h"
#include "battle.h"
#include "cursor.h"
#include "field.h"

class CursorController {
	private:
		Cursor& m_cursor;
		Battle& m_battle;
		static constexpr int BENCH_START = 0;
		static constexpr int BENCH_END = 4;
		static constexpr int ACTIVE = 5;
		static constexpr int STADIUM = 6;
		static constexpr int OPP_ACTIVE = 7;
		static constexpr int OPP_BENCH_START = 8;
		static constexpr int OPP_BENCH_END = 12;
		void snap(int i);
	public:
		CursorController(Cursor& cursor, Battle& battle);
		void update();
};

#endif // GUARD_CURSOR_CONTROLLER_H