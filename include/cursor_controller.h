#ifndef GUARD_CURSOR_CONTROLLER_H
#define GUARD_CURSOR_CONTROLLER_H

#include "battle_engine.h"
#include "cursor.h"
#include "field.h"

class CursorController {
	private:
		Cursor& m_cursor;
		BattleEngine& m_battle_engine;
	public:
		CursorController(Cursor& cursor, BattleEngine& battle_engine);
		void update();
	private:
		void snap_to_zone(ZoneId id, Side side=Side::SIDE_PLAYER);
};

#endif // GUARD_CURSOR_CONTROLLER_H