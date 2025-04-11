#ifndef GUARD_COIN_FLIPPER_H
#define GUARD_COIN_FLIPPER_H

#include "bn_optional.h"
#include "bn_sprite_animate_actions.h"

enum class CoinResult {
	HEADS,
	TAILS
};

class CoinFlipper {
	private:
		bool m_flipping = false;
		CoinResult m_result;
		bn::optional<bn::sprite_ptr> m_sprite;
		bn::optional<bn::sprite_animate_action<9>> m_anim;
	public:
		CoinFlipper();
		void update();
		void start_flip();
		bool done() const;
		CoinResult result() const;
		void destroy();
};

#endif // GUARD_COIN_FLIPPER_H