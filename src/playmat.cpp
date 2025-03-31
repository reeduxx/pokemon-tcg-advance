#include "bn_regular_bg_items_playmat.h"
#include "playmat.h"

Playmat::Playmat() : m_bg(bn::regular_bg_items::playmat.create_bg()), m_scroll_curr(0, -48), m_scroll_target(0, -48) {
	m_bg.set_position(m_scroll_curr);
	// Player bench
	m_zones.push_back({{-54, 15}});
	m_zones.push_back({{-27, 15}});
	m_zones.push_back({{0, 15}});
	m_zones.push_back({{27, 15}});
	m_zones.push_back({{54, 15}});
	// Player active
	m_zones.push_back({{0, -24}});
	// Stadium
	m_zones.push_back({{-23, -9}});
	// Opponent active
	m_zones.push_back({{0, 24}});
	// Opponent bench
	m_zones.push_back({{-54, -15}});
	m_zones.push_back({{-27, -15}});
	m_zones.push_back({{0, -15}});
	m_zones.push_back({{27, -15}});
	m_zones.push_back({{54, -15}});
}

void Playmat::update() {
	if(m_scroll_curr != m_scroll_target) {
		bn::fixed dy = (m_scroll_target.y() - m_scroll_curr.y()) / 4;
		m_scroll_curr += bn::fixed_point(0, dy);
		m_bg.set_position(m_scroll_curr);
	}
}

void Playmat::scroll_to_player() {
	m_scroll_target = bn::fixed_point(0, -48);
}

void Playmat::scroll_to_opponent() {
	m_scroll_target = bn::fixed_point(0, 48);
}

const Zone& Playmat::get_zone(int i) const {
	return m_zones[i];
}

Zone& Playmat::get_zone(int i) {
	return m_zones[i];
}

int Playmat::zone_count() const {
	return m_zones.size();
}