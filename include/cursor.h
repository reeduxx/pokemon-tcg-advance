#ifndef GUARD_CURSOR_H
#define GUARD_CURSOR_H

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "zone.h"

enum class CursorMode {
	FIELD,
	HAND
};

class Cursor {
	private:
		bn::sprite_ptr m_sprite;
		bn::fixed_point m_pos;
		int m_timer;
		CursorMode m_mode = CursorMode::HAND;
		ZoneId m_zone_id = ZoneId::PLAYER_BENCH_1;
		int m_hand_idx = 0;
	public:
		Cursor();
		void update();
		void set_pos(bn::fixed_point pos);
		bn::fixed_point position() const;
		void set_zone(ZoneId id);
		ZoneId zone() const;
		void set_mode(CursorMode mode);
		CursorMode mode() const;
		void set_hand_idx(int i);
		int hand_idx() const;
		void set_visible(bool visible);
};

#endif // GUARD_CURSOR_H