#ifndef CARD_H
#define CARD_H

#include <cstdint>

enum class CardType : uint8_t {
	CARD_POKEMON,
	CARD_TRAINER,
	CARD_ENERGY,
	NONE = 0xFF
};

enum class Set : uint8_t {
	SET_BASE_SET,
	SET_JUNGLE,
	SET_FOSSIL,
	SET_BASE_SET_2, // Reprint set
	SET_TEAM_ROCKET,
	SET_GYM_HEROES,
	SET_GYM_CHALLENGE,
	SET_NEO_GENESIS,
	SET_NEO_DISCOVERY,
	SET_NEO_REVELATION,
	SET_NEO_DESTINY,
	SET_LEGENDARY_COLLECTION, // Reprint set
	SET_EXPEDITION_BASE_SET,
	SET_AQUAPOLIS,
	SET_SKYRIDGE,
	SET_EX_RUBY_SAPPHIRE,
	SET_EX_SANDSTORM,
	SET_EX_DRAGON,
	SET_EX_TEAM_MAGMA_VS_TEAM_AQUA,
	SET_EX_HIDDEN_LEGENDS,
	SET_EX_FIRERED_LEAFGREEN,
	SET_EX_TEAM_ROCKET_RETURNS,
	SET_EX_DEOXYS,
	SET_EX_EMERALD,
	SET_EX_UNSEEN_FORCES,
	SET_EX_DELTA_SPECIES,
	SET_EX_LEGEND_MAKER,
	SET_EX_HOLON_PHANTOMS,
	SET_EX_CRYSTAL_GUARDIANS,
	SET_EX_DRAGON_FRONTIERS,
	SET_EX_POWER_KEEPERS,
	NONE = 0xFF
};

enum class Rarity : uint8_t {
	RARITY_COMMON,
	RARITY_UNCOMMON,
	RARITY_RARE,
	RARITY_HOLO,
	RARITY_SECRET,
	RARITY_PROMO,
	NONE = 0xFF
};

enum class Type : uint8_t {
	TYPE_GRASS,
	TYPE_FIRE,
	TYPE_WATER,
	TYPE_LIGHTNING,
	TYPE_FIGHTING,
	TYPE_PSYCHIC,
	TYPE_COLORLESS,
	TYPE_DARKNESS,
	TYPE_METAL,
	NONE = 0xFF
};

enum class TrainerSubtype : uint8_t {
	SUBTYPE_ITEM,
	SUBTYPE_SUPPORTER,
	SUBTYPE_STADIUM,
	SUBTYPE_TOOL,
	SUBTYPE_TM,
	NONE = 0xFF
};

struct CardHeader {
	uint16_t id;
	CardType type;
	uint8_t name_id;
	Set set;
	uint8_t set_number;
	Rarity rarity;
};

struct PokemonData {
	uint8_t stage;
	uint8_t evolution_from;
	Type primary_type;
	Type secondary_type;
	uint8_t hp;
	Type weakness;
	Type resistance;
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
	Type element;
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