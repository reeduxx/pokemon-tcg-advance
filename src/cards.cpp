#include "cards.h"
#include "card_ids.h"


#define POKEMON_CARD(uuid, name_id, set, set_id, rarity, ...) \
	{.header = {uuid, CardType::POKEMON, name_id, set, set_id, rarity}, .pokemon = {__VA_ARGS__}}
/*
Pokemon
{
	.header = {
		GLOBAL_ID,
		POKEMON,
		NAME_ID,
		SET_ID,
		SET_NUM,
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
	POKEMON_CARD(UUID::BASE_SET_ALAKAZAM, 0, SetId::BASE_SET, 1, Rarity::HOLO, 3, 0, ElementType::PSYCHIC, ElementType::NONE, 80, ElementType::PSYCHIC, ElementType::NONE, 3, 0, 0, 0),
	POKEMON_CARD(UUID::BASE_SET_BLASTOISE, 0, SetId::BASE_SET, 2, Rarity::HOLO, 3, 0, ElementType::WATER, ElementType::NONE, 100, ElementType::LIGHTNING, ElementType::NONE, 3, 0, 0, 0),
	POKEMON_CARD(UUID::BASE_SET_CHANSEY, 0, SetId::BASE_SET, 3, Rarity::HOLO, 1, 0, ElementType::COLORLESS, ElementType::NONE, 120, ElementType::FIGHTING, ElementType::PSYCHIC, 1, 0, 0, 0),
	POKEMON_CARD(UUID::BASE_SET_CHARIZARD, 0, SetId::BASE_SET, 4, Rarity::HOLO, 3, 0, ElementType::FIRE, ElementType::NONE, 120, ElementType::WATER, ElementType::FIGHTING, 3, 0, 0, 0),
	POKEMON_CARD(UUID::BASE_SET_CLEFAIRY, 0, SetId::BASE_SET, 5, Rarity::HOLO, 1, 0, ElementType::COLORLESS, ElementType::NONE, 40, ElementType::FIGHTING, ElementType::PSYCHIC, 1, 0, 0, 0),
	POKEMON_CARD(UUID::BASE_SET_GYARADOS, 0, SetId::BASE_SET, 6, Rarity::HOLO, 2, 0, ElementType::WATER, ElementType::NONE, 100, ElementType::GRASS, ElementType::FIGHTING, 3, 0, 0, 0),
	POKEMON_CARD(UUID::BASE_SET_HITMONCHAN, 0, SetId::BASE_SET, 7, Rarity::HOLO, 1, 0, ElementType::FIGHTING, ElementType::NONE, 70, ElementType::PSYCHIC, ElementType::NONE, 2, 0, 0, 0),
	POKEMON_CARD(UUID::BASE_SET_MACHAMP, 0, SetId::BASE_SET, 8, Rarity::HOLO, 3, 0, ElementType::FIGHTING, ElementType::NONE, 100, ElementType::PSYCHIC, ElementType::NONE, 3, 0, 0, 0),
	POKEMON_CARD(UUID::BASE_SET_MAGNETON, 0, SetId::BASE_SET, 9, Rarity::HOLO, 2, 0, ElementType::LIGHTNING, ElementType::NONE, 60, ElementType::FIGHTING, ElementType::NONE, 1, 0, 0, 0),
	POKEMON_CARD(UUID::BASE_SET_MEWTWO, 0, SetId::BASE_SET, 10, Rarity::HOLO, 1, 0, ElementType::PSYCHIC, ElementType::NONE, 60, ElementType::PSYCHIC, ElementType::NONE, 3, 0, 0, 0,),
	POKEMON_CARD(UUID::BASE_SET_NIDOKING, 0, SetId::BASE_SET, 11, Rarity::HOLO, 3, 0, ElementType::GRASS, ElementType::NONE, 90, ElementType::PSYCHIC, ElementType::NONE, 3, 0, 0, 0),
	POKEMON_CARD(UUID::BASE_SET_NINETALES, 0, SetId::BASE_SET, 12, Rarity::HOLO, 2, 0, ElementType::FIRE, ElementType::NONE, 80, ElementType::WATER, ElementType::NONE, 1, 0, 0, 0),
	POKEMON_CARD(UUID::BASE_SET_POLIWRATH, 0, SetId::BASE_SET, 13, Rarity::HOLO, 3, 0, ElementType::WATER, ElementType::NONE, 90, ElementType::GRASS, ElementType::NONE, 3, 0, 0, 0),
	POKEMON_CARD(UUID::BASE_SET_RAICHU, 0, SetId::BASE_SET, 14, Rarity::HOLO, 2, 0, ElementType::LIGHTNING, ElementType::NONE, 80, ElementType::FIGHTING, ElementType::NONE, 1, 0, 0, 0),
	POKEMON_CARD(UUID::BASE_SET_VENUSAUR, 0, SetId::BASE_SET, 15, Rarity::HOLO, 3, 0, ElementType::GRASS, ElementType::NONE, 100, ElementType::FIRE, ElementType::NONE, 2, 0, 0, 0),
	POKEMON_CARD(UUID::BASE_SET_ZAPDOS, 0, SetId::BASE_SET, 16, Rarity::HOLO, 1, 0, ElementType::LIGHTNING, ElementType::NONE, 90, ElementType::NONE, ElementType::FIGHTING, 3, 0, 0, 0)
};

const uint16_t CARD_DATABASE_SIZE = sizeof(cards) / sizeof(Card);

const Card* get_card_by_id(uint16_t id) {
	if(id >= CARDS_SIZE) {
		return nullptr;
	}
	
	return &cards[id];
}