#include "bn_math.h"
#include "bn_sprite_items_battle_cursor.h"
#include "battle_cursor.h"

BattleCursor::BattleCursor() : Cursor(bn::sprite_items::battle_cursor) {}

void BattleCursor::update() {
    ++m_timer;
    int angle = (m_timer * 16) & 2047;
    int offset = (bn::lut_sin(angle) * 2).round_integer();
    m_sprite.set_position(m_pos.x(), m_pos.y() + offset);
}

void BattleCursor::set_pos(bn::fixed_point pos) {
    m_pos = pos;
    m_sprite.set_position(pos);
}

bn::fixed_point BattleCursor::pos() const {
    return m_pos;
}

void BattleCursor::set_visible(bool visible) {
    m_sprite.set_visible(visible);
}

void BattleCursor::set_zone(ZoneId zone_id) {
    m_zone_id = zone_id;
}

ZoneId BattleCursor::zone() const {
    return m_zone_id;
}

void BattleCursor::set_mode(CursorMode mode) {
    m_mode = mode;
}

CursorMode BattleCursor::mode() const {
    return m_mode;
}

void BattleCursor::set_hand_idx(int i) {
    m_hand_idx = i;
}

int BattleCursor::hand_idx() const {
    return m_hand_idx;
}