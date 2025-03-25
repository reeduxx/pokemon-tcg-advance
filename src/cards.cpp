#include "cards.h"

/*
Pokemon
{
	.header = {
		GLOBAL_ID,
		POKEMON,
		NAME_ID,
		SET_ID,
		RARITY
	},
	.pokemon = {
		STAGE,
		EVO,
		TYPE_1,
		TYPE_2,
		HP,
		WEAKNESS,
		RESISTANCE,
		RETREAT,
		ABILITY,
		ATTACK_1,
		ATTACK_2
	}
}
*/

const Card cards[] = {
	// Base Set
	{
		.header = {
			0, 
			POKEMON, 
			0, 
			SetId::BASE_SET, 
			Rarity::HOLO
		},
		.pokemon = {
			3,
			0,
			ElementType::PSYCHIC, ElementType::NONE,
			80,
			ElementType::PSYCHIC,
			ELEMENTTYPE::NONE,
			3,
			0,
			0,
			0
		}
	},
	{
		.header = {
			1,
			POKEMON,
			0,
			SetId::BASE_SET,
			Rarity::HOLO
		},
		.pokemon = {
			
		}
	}
};

const uint16_t CARD_DATABASE_SIZE = sizeof(cards) / sizeof(Card);

const Card* get_card_by_id(uint16_t id) {
	if(id >= CARDS_SIZE) {
		return nullptr;
	}
	
	return &cards[id];
}