#ifndef GUARD_HAND_H
#define GUARD_HAND_H

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "battle_card.h"
#include "deck.h"

class Hand {
	private:
		static constexpr int MAX_HAND_SIZE = 10;
		bn::vector<BattleCard, MAX_HAND_SIZE> m_cards;
		bn::vector<bn::sprite_ptr, MAX_HAND_SIZE> m_sprites;
		bn::vector<bn::fixed_point, MAX_HAND_SIZE> m_pos;
		bool m_is_opponent;
	public:
		Hand(bool is_opponent = false);
		void add_card(BattleCard card);
		void remove_card(int i);
		void update();
		void set_pos(int i, bn::fixed_point pos);
		int card_count() const;
		BattleCard& get_card(int i);
		const BattleCard& get_card(int i) const;
		bn::fixed_point get_card_pos(int i) const;
		void set_visible(bool visible);
		void shuffle_into(Deck& deck);
};

#endif // GUARD_HAND_H