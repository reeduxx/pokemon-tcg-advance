#ifndef GUARD_FIELD_H
#define GUARD_FIELD_H

#include "bn_fixed_point.h"
#include "bn_regular_bg_ptr.h"
#include "bn_vector.h"

struct Zone {
	bn::fixed_point m_pos;
	int m_card_id = -1;
	bool m_is_visible = true;
	bool m_is_active = false;
	
	Zone(bn::fixed_point pos, int card_id = -1, bool is_visible = true, bool is_active = false) : m_pos(pos), m_card_id(card_id), m_is_visible(is_visible), m_is_active(is_active) {}
};

class Field {
	private:
		bn::regular_bg_ptr m_bg;
		bn::fixed_point m_scroll_curr;
		bn::fixed_point m_scroll_target;
		bn::vector<Zone, 17> m_zones;
	public:
		Field();
		void update();
		void scroll_to_player();
		void scroll_to_opponent();
		const Zone& get_zone(int i) const;
		Zone& get_zone(int i);
		int zone_count() const;
};

#endif // GUARD_FIELD_H