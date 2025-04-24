#ifndef GUARD_FONT_H
#define GUARD_FONT_H

#include "bn_sprite_items_font.h"
#include "bn_utf8_characters_map.h"
#include "bn_sprite_items_font.h"

namespace font {
    // constexpr bn::utf8_character font_utf8_characters[] = {};

    // constexpr bn::span<const bn::utf8_character> font_utf8_characters_span(font_utf8_characters);

    // constexpr auto font_utf8_characters_map = bn::utf8_characters_map<font_utf8_characters_span>();

    constexpr bn::sprite_font font(bn::sprite_items::font/*, font_utf8_characters_map.reference()*/);
}

#endif // GUARD_FONT_H