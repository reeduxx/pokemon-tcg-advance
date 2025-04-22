#ifndef GUARD_MENU_CURSOR_CONTROLLER_H
#define GUARD_MENU_CURSOR_CONTROLLER_H

#include "cursor_controller.h"
#include "menu.h"
#include "menu_cursor.h"

class MenuCursorController : public CursorController {
    private:
        MenuCursor& m_cursor;
        Menu& m_menu;
    public:
        MenuCursorController(MenuCursor& cursor, Menu& menu);
        void update() override;
};

#endif // GUARD_MENU_CURSOR_CONTROLLER_H