#ifndef GUARD_CURSOR_H
#define GUARD_CURSOR_H

#include "bn_fixed_point.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"

class Cursor {
    protected:
        bn::sprite_ptr m_sprite;
        bn::fixed_point m_pos;
    public:
        virtual ~Cursor() = default;
        virtual void update() = 0;
        virtual void set_pos(bn::fixed_point pos) = 0;
        virtual bn::fixed_point pos() const = 0;
        virtual void set_visible(bool visible) = 0;
    protected:
        Cursor(const bn::sprite_item& sprite);
};

#endif // GUARD_CURSOR_H