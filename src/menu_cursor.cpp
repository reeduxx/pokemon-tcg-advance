#include "bn_sprite_items_menu_cursor.h"
#include "menu_cursor.h"

MenuCursor::MenuCursor() : Cursor(bn::sprite_items::menu_cursor) {}

void MenuCursor::update() {
    // TODO: Implement update method
}

void MenuCursor::set_pos(bn::fixed_point pos) {
    m_pos = pos;
    m_sprite.set_position(pos);
}

bn::fixed_point MenuCursor::pos() const {
    return m_pos;
}

void MenuCursor::set_visible(bool visible) {
    m_sprite.set_visible(visible);
}

void MenuCursor::set_idx(int i) {
    m_index = i;
}

int MenuCursor::idx() const {
    return m_index;
}