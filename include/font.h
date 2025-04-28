#ifndef GUARD_FONT_H
#define GUARD_FONT_H

#include "bn_sprite_items_font.h"
#include "bn_utf8_characters_map.h"
#include "bn_sprite_items_font.h"

namespace font {
    constexpr bn::utf8_character font_utf8_characters[] = {"¡", "×", "¿", "À", "Á", "Â", "Ã", "Ä"};

    constexpr int8_t font_character_widths[] = {
    3, // 32
    3, // 33 !
    6, // 34 "
    0, // 35 # unused
    7, // 36 $
    0, // 37 % unused
    7, // 38 &
    3, // 39 '
    3, // 40 (
    3, // 41 )
    0, // 42 * unused
    7, // 43 +
    4, // 44 ,
    7, // 45 -
    4, // 46 .
    7, // 47 /
    7, // 48 0
    7, // 49 1
    7, // 50 2
    7, // 51 3
    7, // 52 4
    7, // 53 5
    7, // 54 6
    7, // 55 7
    7, // 56 8
    7, // 57 9
    4, // 58 :
    4, // 59 ;
    7, // 60 <
    7, // 61 =
    7, // 62 >
    7, // 63 ?
    0, // 64 @ unused
    7, // 65 A
    7, // 66 B
    7, // 67 C
    7, // 68 D
    7, // 69 E
    7, // 70 F
    7, // 71 G
    7, // 72 H
    7, // 73 I
    7, // 74 J
    7, // 75 K
    7, // 76 L
    7, // 77 M
    7, // 78 N
    7, // 79 O
    7, // 80 P
    7, // 81 Q
    7, // 82 R
    7, // 83 S
    7, // 84 T
    7, // 85 U
    7, // 86 V
    7, // 87 W
    7, // 88 X
    7, // 89 Y
    7, // 90 Z
    0, // 91 [ unused
    0, // 92   unused
    0, // 93 ] unused
    0, // 94 ^ unused
    7, // 95 _
    0, // 96 ` unused
    7, // 97 a
    7, // 98 b
    7, // 99 c
    7, // 100 d
    7, // 101 e
    7, // 102 f
    7, // 103 g
    7, // 104 h
    3, // 105 i
    6, // 106 j
    7, // 107 k
    3, // 108 l
    7, // 109 m
    7, // 110 n
    7, // 111 o
    7, // 112 p
    7, // 113 q
    6, // 114 r
    7, // 115 s
    7, // 116 t
    7, // 117 u
    7, // 118 v
    7, // 119 w
    7, // 120 x
    7, // 121 y
    7, // 122 z
    0, // 123 { unused
    0, // 124 | unused
    0, // 125 } unused
    0, // 126 ~ unused
    3, // ¡
    7, // ×
    7, // ¿
    7, // À
    7, // Á
    7, // Â
    7, // Ã
    7, // Ä
    };

    constexpr bn::span<const bn::utf8_character> font_utf8_characters_span(font_utf8_characters);

    constexpr auto font_utf8_characters_map = bn::utf8_characters_map<font_utf8_characters_span>();

    constexpr bn::sprite_font font(bn::sprite_items::font, font_utf8_characters_map.reference(), font_character_widths);
}

#endif // GUARD_FONT_H