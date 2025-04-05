#include "bn_sprite_items_card_back.h"
#include "bn_sprite_items_card_sheet_1.h"
#include "bn_sprite_items_card_sheet_2.h"
#include "bn_sprite_items_card_sheet_3.h"
#include "card.h"
#include "cards.h"
#include "hand.h"

Hand::Hand(bool is_opponent) : m_is_opponent(is_opponent) {}

void Hand::add_card(BattleCard card) {
	if(m_cards.full()) {
		return;
	}
	
	// m_cards.push_back(card);
	int index = m_cards.size() - 1;
	bn::fixed_point pos(-75 + index * 25, m_is_opponent ? -60 : 60);
	bn::sprite_ptr sprite = bn::sprite_items::card_sheet_3.create_sprite(pos, 1);
	
	if(m_is_opponent) {
		sprite = bn::sprite_items::card_back.create_sprite(pos);
		sprite.set_vertical_flip(true);
	} else {
		const Card* card_ptr = get_card_by_id(card.card_id);
		
		if(!card_ptr) {
			return;
		}
		
		const Card& card_data = *card_ptr;
		
		if(card_data.pokemon.primary_type == Type::TYPE_GRASS)
			sprite = bn::sprite_items::card_sheet_1.create_sprite(pos, 0);
		if(card_data.pokemon.primary_type == Type::TYPE_FIRE)
			sprite = bn::sprite_items::card_sheet_1.create_sprite(pos, 1);
		if(card_data.pokemon.primary_type == Type::TYPE_WATER)
			sprite = bn::sprite_items::card_sheet_1.create_sprite(pos, 2);
		if(card_data.pokemon.primary_type == Type::TYPE_LIGHTNING)
			sprite = bn::sprite_items::card_sheet_1.create_sprite(pos, 3);
		if(card_data.pokemon.primary_type == Type::TYPE_FIGHTING)
			sprite = bn::sprite_items::card_sheet_2.create_sprite(pos, 0);
		if(card_data.pokemon.primary_type == Type::TYPE_PSYCHIC)
			sprite = bn::sprite_items::card_sheet_2.create_sprite(pos, 1);
		if(card_data.pokemon.primary_type == Type::TYPE_COLORLESS)
			sprite = bn::sprite_items::card_sheet_2.create_sprite(pos, 2);
		if(card_data.pokemon.primary_type == Type::TYPE_DARKNESS)
			sprite = bn::sprite_items::card_sheet_2.create_sprite(pos, 3);
		if(card_data.pokemon.primary_type == Type::TYPE_METAL)
			sprite = bn::sprite_items::card_sheet_3.create_sprite(pos, 0);
	}
	/*
	const Card* card_ptr = get_card_by_id(card.card_id);
	
	if(!card_ptr) {
		m_cards.pop_back();
		return;
	}
	
	const Card& card_data = *card_ptr;
	bn::sprite_ptr sprite = bn::sprite_items::card_sheet_3.create_sprite(pos, 1);
	
	if(card_data.pokemon.primary_type == Type::TYPE_GRASS)
		sprite = bn::sprite_items::card_sheet_1.create_sprite(pos, 0);
	if(card_data.pokemon.primary_type == Type::TYPE_FIRE)
		sprite = bn::sprite_items::card_sheet_1.create_sprite(pos, 1);
	if(card_data.pokemon.primary_type == Type::TYPE_WATER)
		sprite = bn::sprite_items::card_sheet_1.create_sprite(pos, 2);
	if(card_data.pokemon.primary_type == Type::TYPE_LIGHTNING)
		sprite = bn::sprite_items::card_sheet_1.create_sprite(pos, 3);
	if(card_data.pokemon.primary_type == Type::TYPE_FIGHTING)
		sprite = bn::sprite_items::card_sheet_2.create_sprite(pos, 0);
	if(card_data.pokemon.primary_type == Type::TYPE_PSYCHIC)
		sprite = bn::sprite_items::card_sheet_2.create_sprite(pos, 1);
	if(card_data.pokemon.primary_type == Type::TYPE_COLORLESS)
		sprite = bn::sprite_items::card_sheet_2.create_sprite(pos, 2);
	if(card_data.pokemon.primary_type == Type::TYPE_DARKNESS)
		sprite = bn::sprite_items::card_sheet_2.create_sprite(pos, 3);
	if(card_data.pokemon.primary_type == Type::TYPE_METAL)
		sprite = bn::sprite_items::card_sheet_3.create_sprite(pos, 0);
	*/
	
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
			buffer = 0;
			break;
		case 9:
			buffer = 2;
			break;
		default:
			buffer = 4;
	}
	
	int card_visual_width = 22 + buffer;
	int total_width = card_visual_width * count;
	int start_x = -total_width / 2 + card_visual_width / 2;
	
	for(int i = 0; i < count; i++) {
		int x = start_x + i * card_visual_width;
		int y = m_is_opponent ? -60 : 60;
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
	return m_pos[i];
}

void Hand::remove_card(int i) {
	if(i < 0 || i >= m_cards.size()) {
		return;
	}
	
	m_cards.erase(m_cards.begin() + i);
	m_sprites[i].set_visible(false);
	m_sprites.erase(m_sprites.begin() + i);
}

void Hand::set_visible(bool visible) {
	for(int i = 0; i < m_sprites.size(); i++) {
		m_sprites[i].set_visible(visible);
	}
}