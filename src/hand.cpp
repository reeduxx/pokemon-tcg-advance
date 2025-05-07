#include "card.h"
#include "cards.h"
#include "hand.h"
#include "sprite_factory.h"

Hand::Hand(bool is_opponent) : m_is_opponent(is_opponent) {}

void Hand::add_card(BattleCard card) {
	if(m_cards.full()) {
		return;
	}
	
	/*
	int index = m_cards.size() - 1;
	bn::fixed_point pos(-75 + index * 25, m_is_opponent ? -60 : 60);
	*/

	if(m_is_opponent) card.is_face_down = true;

	bn::sprite_ptr sprite = SpriteFactory::create_sprite(card, bn::fixed_point(0, 0), m_is_opponent);
	sprite.set_z_order(1);
	m_cards.push_back(card);
	m_sprites.push_back(sprite);
	m_pos.push_back(sprite.position());
}

void Hand::update() {
	int count = m_cards.size();
	
	if(count == 0 || m_cards.size() != m_sprites.size()) {
		return;
	}
	
	int buffer = 3;
	if(count == 10) buffer = 1;
	else if(count == 9) buffer = 2;
	
	int card_visual_width = 22 + buffer;
	int total_width = card_visual_width * count;
	int start_x = -total_width / 2 + card_visual_width / 2;
	
	for(int i = 0; i < count; i++) {
		int x = start_x + i * card_visual_width;
		int y = m_is_opponent ? -61 : 37;
		bn::fixed_point pos(x, y);
		m_pos[i] = pos;
		m_sprites[i].set_position(pos);
	}
}

int Hand::card_count() const {
	return m_cards.size();
}

BattleCard& Hand::get_card(int i) {
	return m_cards[i];
}

const BattleCard& Hand::get_card(int i) const {
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

void Hand::shuffle_into(Deck& deck) {
	while(!m_cards.empty()) {
		BattleCard card = m_cards.back();
		m_cards.pop_back();
		deck.push_back(card);
	}

	for(auto& sprite : m_sprites) {
		sprite.set_visible(false);
	}

	m_sprites.clear();
	m_pos.clear();
	shuffle_deck(deck);
}