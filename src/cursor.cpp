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
	m_sprite.set_position(m_pos);
}

void Cursor::move_by(int dx, int dy) {
	set_pos(m_pos + bn::fixed_point(dx, dy));
}

bn::fixed_point Cursor::position() const {
	return m_sprite.position();
}

void Cursor::snap_to(bn::fixed_point zone) {
	set_pos(zone);
}

void Cursor::set_zone_idx(int i) {
	m_zone_idx = i;
}

int Cursor::zone_idx() const {
	return m_zone_idx;
}