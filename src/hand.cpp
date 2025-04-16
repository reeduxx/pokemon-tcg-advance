#include "card.h"
#include "cards.h"
#include "hand.h"
#include "sprite_factory.h"

Hand::Hand(bool is_opponent) : m_is_opponent(is_opponent) {}

void Hand::add_card(BattleCard card) {
	if(m_cards.full()) {
		return;
	}
	
	int index = m_cards.size() - 1;
	bn::fixed_point pos(-75 + index * 25, m_is_opponent ? -60 : 60);

	if(m_is_opponent) card.is_face_down = true;

	bn::sprite_ptr sprite = SpriteFactory::create_sprite(card, pos, m_is_opponent);
	sprite.set_z_order(1);
	m_cards.push_back(card);
	m_sprites.push_back(sprite);
	m_pos.push_back(pos);
}

void Hand::update() {
	int count = m_cards.size();
	
	if(count == 0) {
		return;
	}
	
	if(m_cards.size() != m_sprites.size() || m_cards.size() != m_pos.size()) {
		return;
	}
	
	int buffer;
	
	switch(m_cards.size()) {
		case 10:
			buffer = 1;
			break;
		case 9:
			buffer = 2;
			break;
		default:
			buffer = 3;
	}
	
	int card_visual_width = 22 + buffer;
	int total_width = card_visual_width * count;
	int start_x = -total_width / 2 + card_visual_width / 2;
	
	for(int i = 0; i < count; i++) {
		int x = start_x + i * card_visual_width;
		int y = m_is_opponent ? -61 : 37;
		m_pos[i] = bn::fixed_point(x, y);
		m_sprites[i].set_position(m_pos[i]);
	}
}

int Hand::card_count() const {
	return m_cards.size();
}

BattleCard Hand::get_card(int i) const {
	return m_cards[i];
}

bn::fixed_point Hand::get_card_pos(int i) const {
	if(i < 0 || i >= m_pos.size()) {
		return bn::fixed_point(0, 0);
	}
	
	return m_pos[i];
}

void Hand::remove_card(int i) {
	if(i < 0 || i >= m_cards.size()) {
		return;
	}
	
	m_cards.erase(m_cards.begin() + i);
	m_pos.erase(m_pos.begin() + i);
	m_sprites[i].set_visible(false);
	m_sprites.erase(m_sprites.begin() + i);
}

void Hand::set_visible(bool visible) {
	for(int i = 0; i < m_sprites.size(); i++) {
		m_sprites[i].set_visible(visible);
	}
}