#include "bn_math.h"
#include "bn_sprite_items_cursor.h"
#include "cursor.h"

Cursor::Cursor() : m_sprite(bn::sprite_items::cursor.create_sprite()), m_pos(0, 0), m_timer(0) {
	m_sprite.set_position(m_pos);
	m_sprite.set_z_order(0);
}

void Cursor::update() {
	++m_timer;
	int angle = (m_timer * 16) & 2047;
	int offset = (bn::lut_sin(angle) * 2).round_integer();
	m_sprite.set_position(m_pos.x(), m_pos.y() + offset);
}

void Cursor::set_pos(bn::fixed_point pos) {
	m_pos = pos;
	m_sprite.set_position(pos);
}

bn::fixed_point Cursor::position() const {
	return m_sprite.position();
}

void Cursor::set_zone(ZoneId id) {
	m_zone_id = id;
}

ZoneId Cursor::zone() const {
	return m_zone_id;
}

void Cursor::set_mode(CursorMode mode) {
	m_mode = mode;
}

CursorMode Cursor::mode() const {
	return m_mode;
}

void Cursor::set_hand_idx(int i) {
	m_hand_idx = i;
}

int Cursor::hand_idx() const {
	return m_hand_idx;
}