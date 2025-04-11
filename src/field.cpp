#include "bn_regular_bg_items_field.h"
#include "field.h"

Field::Field() : m_bg(bn::regular_bg_items::field.create_bg(0, 0)), m_scroll_curr(0, -48), m_scroll_target(0, -48) {
	initialize_zones();
}

void Field::update() {
	if(m_scroll_curr != m_scroll_target) {
		bn::fixed dy = (m_scroll_target.y() - m_scroll_curr.y()) / 4;
		m_scroll_curr += bn::fixed_point(0, dy);
		m_bg.set_position(m_scroll_curr);
	}
}

void Field::scroll_to_player() {
	m_scroll_target = bn::fixed_point(0, -48);
	set_side(Side::SIDE_PLAYER);
}

void Field::scroll_to_opponent() {
	m_scroll_target = bn::fixed_point(0, 48);
	set_side(Side::SIDE_OPPONENT);
}

const Zone& Field::get_zone(ZoneId id) const {
	return m_zones[static_cast<int>(id)];
}

Zone& Field::get_zone(ZoneId id) {
	return m_zones[static_cast<int>(id)];
}

int Field::zone_count() const {
	return m_zones.size();
}

void Field::initialize_zones() {
	m_zones[static_cast<int>(ZoneId::PLAYER_BENCH_1)] = Zone(ZoneId::PLAYER_BENCH_1, bn::fixed_point(-54, 17));
	m_zones[static_cast<int>(ZoneId::PLAYER_BENCH_2)] = Zone(ZoneId::PLAYER_BENCH_2, bn::fixed_point(-27, 17));
	m_zones[static_cast<int>(ZoneId::PLAYER_BENCH_3)] = Zone(ZoneId::PLAYER_BENCH_3, bn::fixed_point(0, 17));
	m_zones[static_cast<int>(ZoneId::PLAYER_BENCH_4)] = Zone(ZoneId::PLAYER_BENCH_4, bn::fixed_point(27, 17));
	m_zones[static_cast<int>(ZoneId::PLAYER_BENCH_5)] = Zone(ZoneId::PLAYER_BENCH_5, bn::fixed_point(54, 17));
	m_zones[static_cast<int>(ZoneId::PLAYER_ACTIVE)] = Zone(ZoneId::PLAYER_ACTIVE, bn::fixed_point(0, -23));
	m_zones[static_cast<int>(ZoneId::STADIUM)] = Zone(ZoneId::STADIUM, bn::fixed_point(-34, -48), bn::fixed_point(-34, 48));
	m_zones[static_cast<int>(ZoneId::OPPONENT_ACTIVE)] = Zone(ZoneId::OPPONENT_ACTIVE, bn::fixed_point(0, 23));
	m_zones[static_cast<int>(ZoneId::OPPONENT_BENCH_1)] = Zone(ZoneId::OPPONENT_BENCH_1, bn::fixed_point(-54, -17));
	m_zones[static_cast<int>(ZoneId::OPPONENT_BENCH_2)] = Zone(ZoneId::OPPONENT_BENCH_2, bn::fixed_point(-27, -17));
	m_zones[static_cast<int>(ZoneId::OPPONENT_BENCH_3)] = Zone(ZoneId::OPPONENT_BENCH_3, bn::fixed_point(0, -17));
	m_zones[static_cast<int>(ZoneId::OPPONENT_BENCH_4)] = Zone(ZoneId::OPPONENT_BENCH_4, bn::fixed_point(27, -17));
	m_zones[static_cast<int>(ZoneId::OPPONENT_BENCH_5)] = Zone(ZoneId::OPPONENT_BENCH_5, bn::fixed_point(54, -17));
}

void Field::set_side(Side side) {
	m_side = side;
}

Side Field::side() const {
	return m_side;
}