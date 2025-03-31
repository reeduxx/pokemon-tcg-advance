#ifndef GUARD_CURSOR_H
#define GUARD_CURSOR_H

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"

class Cursor {
	private:
		bn::sprite_ptr m_sprite;
		bn::fixed_point m_pos;
		int m_timer;
		int m_zone_idx = 0;
	public:
		Cursor();
		void update();
		void set_pos(bn::fixed_point pos);
		void move_by(int dx, int dy);
		bn::fixed_point position() const;
		void snap_to(bn::fixed_point zone);
		void set_zone_idx(int i);
		int zone_idx() const;
};

#endif // GUARD_CURSOR_H