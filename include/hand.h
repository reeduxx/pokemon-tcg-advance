#ifndef GUARD_HAND_H
#define GUARD_HAND_H

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

class Hand {
	private:
		static constexpr int MAX_HAND_SIZE = 10;
		bn::vector<int, MAX_HAND_SIZE> m_cards;
		bn::vector<bn::sprite_ptr, MAX_HAND_SIZE> m_sprites;
		bn::array<bn::fixed_point, MAX_HAND_SIZE> m_pos;
	public:
		Hand();
		void add_card(int id);
		void remove_card(int i);
		void update();
		void set_pos(int i, bn::fixed_point pos);
		int card_count() const;
		int get_card_id(int i) const;
		bn::fixed_point get_card_pos(int i) const;
};

#endif // GUARD_HAND_H