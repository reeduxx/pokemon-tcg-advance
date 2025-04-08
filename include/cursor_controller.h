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
	public:
		CursorController(Cursor& cursor, Battle& battle);
		void update();
	private:
		void snap_to_zone(ZoneId id, Side side=Side::SIDE_PLAYER);
};

#endif // GUARD_CURSOR_CONTROLLER_H