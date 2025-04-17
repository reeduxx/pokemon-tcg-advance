#ifndef GUARD_CARD_NAME_BAR_H
#define GUARD_CARD_NAME_BAR_H

#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_vector.h"

class CardNameBar {
    private:
        bn::regular_bg_ptr m_bg;
        bn::sprite_text_generator& m_text_generator;
        bn::vector<bn::sprite_ptr, 32> m_text_sprites;
        bn::string<32> m_text;
    public:
        CardNameBar(const bn::regular_bg_item& bg, bn::sprite_text_generator& text_generator);
        void update();
        void set_text(const bn::string<32>& text);
        void clear();
        void show();
        void hide();
};

#endif // GUARD_CARD_NAME_BAR_H