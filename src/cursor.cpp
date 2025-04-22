#include "cursor.h"

Cursor::Cursor(const bn::sprite_item& sprite) : m_sprite(sprite.create_sprite(0, 0)) {
    m_sprite.set_z_order(0);
    m_sprite.set_position(m_pos);
}