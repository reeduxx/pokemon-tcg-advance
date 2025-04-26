#ifndef GUARD_BATTLE_CURSOR_H
#define GUARD_BATTLE_CURSOR_H

#include "cursor.h"
#include "zone.h"

enum class CursorMode {
    HAND,
    FIELD,
    TARGET
};

class BattleCursor : public Cursor {
    private:
        CursorMode m_mode;
        ZoneId m_zone_id;
        int m_hand_idx;
        int m_timer = 0;
    public:
        BattleCursor();
        void update() override;
        void set_pos(bn::fixed_point pos) override;
        bn::fixed_point pos() const override;
        void set_visible(bool visible) override;
        void set_zone(ZoneId zone_id);
        ZoneId zone() const;
        void set_mode(CursorMode mode);
        CursorMode mode() const;
        void set_hand_idx(int i);
        int hand_idx() const;
};

#endif // GUARD_BATTLE_CURSOR_H