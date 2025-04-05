#ifndef GUARD_ZONE_H
#define GUARD_ZONE_H

enum class ZoneId {
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
	ZONE_COUNT
};

struct Zone {
	ZoneId m_zone;
	bn::fixed_point m_pos;
	bool occupied = false;
	Zone() = default;
	Zone(ZoneId zone, bn::fixed_point pos) : m_zone(zone), m_pos(pos) {}
};

#endif // GUARD_ZONE_H