#ifndef GUARD_MENU_CURSOR_H
#define GUARD_MENU_CURSOR_H

#include "bn_vector.h"
#include "cursor.h"

class MenuCursor : public Cursor {
    private:
        int m_index = 0;
    public:
        MenuCursor();
        void update() override;
        void set_pos(bn::fixed_point pos) override;
        bn::fixed_point pos() const override;
        void set_visible(bool visible) override;
        void set_idx(int i);
        int idx() const;
};

#endif // GUARD_MENU_CURSOR_H