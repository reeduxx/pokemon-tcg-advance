#ifndef CARD_H
#define CARD_H

#include <cstdint>

enum class CardType : uint8_t {
	POKEMON,
	TRAINER,
	ENERGY,
	NONE = 0xFF
};

enum class SetId : uint8_t {
	BASE_SET,
	JUNGLE,
	FOSSIL,
	BASE_SET_2,
	TEAM_ROCKET,
	GYM_HEROES,
	GYM_CHALLENGE,
	NEO_GENESIS,
	NEO_DISCOVERY,
	NEO_REVELATION,
	NEO_DESTINY,
	LEGENDARY_COLLECTION,
	EXPEDITION_BASE_SET,
	AQUAPOLIS,
	SKYRIDGE,
	EX_RUBY_SAPPHIRE,
	EX_SANDSTORM,
	EX_DRAGON,
	EX_TEAM_MAGMA_VS_TEAM_AQUA,
	EX_HIDDEN_LEGENDS,
	EX_FIRERED_LEAFGREEN,
	EX_TEAM_ROCKET_RETURNS,
	EX_DEOXYS,
	EX_EMERALD,
	EX_UNSEEN_FORCES,
	EX_DELTA_SPECIES,
	EX_LEGEND_MAKER,
	EX_HOLON_PHANTOMS,
	EX_CRYSTAL_GUARDIANS,
	EX_DRAGON_FRONTIERS,
	EX_POWER_KEEPERS,
	NONE = 0xFF
};

enum class Rarity : uint8_t {
	COMMON,
	UNCOMMON,
	RARE,
	HOLO,
	SECRET,
	NONE = 0xFF
};

enum class ElementType : uint8_t {
	GRASS,
	FIRE,
	WATER,
	LIGHTNING,
	FIGHTING,
	PSYCHIC,
	COLORLESS,
	DARKNESS,
	METAL,
	NONE = 0xFF
};

enum class TrainerSubtype : uint8_t {
	ITEM,
	SUPPORTER,
	STADIUM,
	NONE = 0xFF
};

struct CardHeader {
	uint16_t id;
	CardType type;
	uint8_t name_id;
	SetId set_id;
	Rarity rarity;
};

struct PokemonData {
	uint8_t stage;
	uint8_t evolution_from;
	ElementType primary_element;
	ElementType secondary_element;
	uint8_t hp;
	ElementType weakness;
	ElementType resistance;
	uint8_t retreat_cost;
	uint8_t ability_id;
	uint8_t attack1_id;
	uint8_t attack2_id;
};

struct TrainerData {
	TrainerSubtype subtype;
	uint8_t effect_id;
};

struct EnergyData {
	ElementType element;
	uint8_t special;
};

struct Card {
	CardHeader header;
	
	union {
		PokemonData pokemon;
		TrainerData trainer;
		EnergyData energy;
	};
};

#endif // CARD_H