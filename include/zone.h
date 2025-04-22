#ifndef GUARD_ZONE_H
#define GUARD_ZONE_H

#include "bn_sprite_ptr.h"
#include "battle_card.h"

enum class ZoneId {
	PLAYER_DECK,
	PLAYER_DISCARD,
	PlAYER_PRIZES,
	PLAYER_BENCH_1,
	PLAYER_BENCH_2,
	PLAYER_BENCH_3,
	PLAYER_BENCH_4,
	PLAYER_BENCH_5,
	PLAYER_ACTIVE,
	STADIUM,
	OPPONENT_ACTIVE,
	OPPONENT_BENCH_1,
	OPPONENT_BENCH_2,
	OPPONENT_BENCH_3,
	OPPONENT_BENCH_4,
	OPPONENT_BENCH_5,
	OPPONENT_PRIZES,
	OPPONENT_DISCARD,
	OPPONENT_DECK,
	ZONE_COUNT
};

struct Zone {
	ZoneId m_zone;
	bn::fixed_point m_pos;
	bn::fixed_point m_opponent_pos;
	bool occupied = false;
	BattleCard card;
	bn::optional<bn::sprite_ptr> sprite;
	Zone() = default;
	Zone(ZoneId zone, bn::fixed_point pos, bn::fixed_point opponent_pos=bn::fixed_point(0,0)) : m_zone(zone), m_pos(pos), m_opponent_pos(opponent_pos) {}
	void set_visible(bool visible) { if(sprite.has_value()) sprite->set_visible(visible); }
};

#endif // GUARD_ZONE_H