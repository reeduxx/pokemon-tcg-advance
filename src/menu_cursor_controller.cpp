#include "bn_keypad.h"
#include "menu_cursor_controller.h"

MenuCursorController::MenuCursorController(MenuCursor& cursor, Menu& menu) : m_cursor(cursor), m_menu(menu) {
    m_cursor.set_idx(0);
}

void MenuCursorController::update() {
    // Up
    if(bn::keypad::up_pressed()) {
        if(m_cursor.idx() > 0) {
            m_cursor.set_idx(m_cursor.idx() - 1);
            m_cursor.set_pos(m_menu.option_pos(m_cursor.idx()));
        }
    }
    // Down
    if(bn::keypad::down_pressed()) {
        if(m_cursor.idx() < m_menu.option_count() - 1) {
            m_cursor.set_idx(m_cursor.idx() + 1);
            m_cursor.set_pos(m_menu.option_pos(m_cursor.idx()));
        }
    }
}