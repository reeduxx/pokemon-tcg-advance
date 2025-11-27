#pragma once

#include "bn_bg_palette_item.h"
#include "bn_regular_bg_tiles_item.h"

struct MenuFrameStyle {
    const bn::regular_bg_tiles_item& tiles;
    const bn::bg_palette_item& pal;
};

extern const MenuFrameStyle frame_styles[];
extern const int frame_styles_count;
