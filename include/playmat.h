#ifndef GUARD_PLAYMAT_H
#define GUARD_PLAYMAT_H

#include "bn_fixed_point.h"
#include "bn_regular_bg_ptr.h"
#include "bn_vector.h"

struct Zone {
	bn::fixed_point pos;
	int card_id = -1;
	bool is_visible = true;
	bool is_active = false;
	
	Zone(bn::fixed_point pos, int card_id = -1, bool is_visible = true, bool is_active = false) : pos(pos), card_id(card_id), is_visible(is_visible), is_active(is_active) {}
};

class Playmat {
	private:
		bn::regular_bg_ptr m_bg;
		bn::fixed_point m_scroll_curr;
		bn::fixed_point m_scroll_target;
		bn::vector<Zone, 17> m_zones;
	public:
		Playmat();
		void update();
		void scroll_to_player();
		void scroll_to_opponent();
		const Zone& get_zone(int i) const;
		Zone& get_zone(int i);
		int zone_count() const;
};

#endif // GUARD_PLAYMAT_H