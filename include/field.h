#ifndef GUARD_FIELD_H
#define GUARD_FIELD_H

#include "bn_array.h"
#include "bn_fixed_point.h"
#include "bn_regular_bg_ptr.h"
#include "zone.h"

enum class Side {
	SIDE_PLAYER,
	SIDE_OPPONENT
};

class Field {
	private:
		bn::regular_bg_ptr m_bg;
		bn::fixed_point m_scroll_curr;
		bn::fixed_point m_scroll_target;
		Side m_side;
		bn::array<Zone, static_cast<int>(ZoneId::ZONE_COUNT)> m_zones;
		void initialize_zones();
		void set_side(Side side);
	public:
		Field();
		void update();
		void scroll_to_player();
		void scroll_to_opponent();
		const Zone& get_zone(ZoneId id) const;
		Zone& get_zone(ZoneId id);
		int zone_count() const;
		Side side() const;
};

#endif // GUARD_FIELD_H