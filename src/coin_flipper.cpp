#include "bn_random.h"
#include "bn_sprite_items_chansey_coin.h"
#include "coin_flipper.h"

CoinFlipper::CoinFlipper() {
	m_sprite = bn::sprite_items::chansey_coin.create_sprite(0, 0);
	m_sprite->set_visible(false);
}

void CoinFlipper::update() {
	if(m_anim.has_value()) {
		m_anim->update();
		
		if(m_anim->done()) {
			m_flipping = false;
		}
	}
}

void CoinFlipper::start_flip() {
	bn::random rand;
	m_flipping = true;
	m_sprite->set_visible(true);
	m_result = (rand.get_int(2) == 0) ? CoinResult::HEADS : CoinResult::TAILS;
	
	if(m_result == CoinResult::HEADS) {
		m_anim = bn::create_sprite_animate_action_once(*m_sprite, 6, bn::sprite_items::chansey_coin.tiles_item(), 0, 1, 3, 5, 6, 4, 3, 2, 0);
	} else {
		m_anim = bn::create_sprite_animate_action_once(*m_sprite, 6, bn::sprite_items::chansey_coin.tiles_item(), 0, 1, 3, 5, 6);
	}
}

bool CoinFlipper::done() const {
	return !m_flipping;
}

CoinResult CoinFlipper::result() const {
	return m_result;
}

void CoinFlipper::destroy() {
	m_flipping = false;
	
	if(m_sprite.has_value()) {
		m_sprite->set_visible(false);
		m_sprite.reset();
	}
	
	if(m_anim.has_value()) {
		m_anim.reset();
	}
}