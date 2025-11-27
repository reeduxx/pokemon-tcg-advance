#ifndef BN_SPRITE_ITEMS_HEALTH_AND_SAFETY_TEXT_3_H
#define BN_SPRITE_ITEMS_HEALTH_AND_SAFETY_TEXT_3_H

#include "bn_sprite_item.h"

//{{BLOCK(health_and_safety_text_3_bn_gfx)

//======================================================================
//
//	health_and_safety_text_3_bn_gfx, 8x32@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles Metatiled by 1x4 not compressed
//	Total size: 32 + 128 = 160
//
//	Time-stamp: 2025-11-23, 00:22:20
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_HEALTH_AND_SAFETY_TEXT_3_BN_GFX_H
#define GRIT_HEALTH_AND_SAFETY_TEXT_3_BN_GFX_H

#define health_and_safety_text_3_bn_gfxTilesLen 128
extern const bn::tile health_and_safety_text_3_bn_gfxTiles[4];

#define health_and_safety_text_3_bn_gfxPalLen 32
extern const bn::color health_and_safety_text_3_bn_gfxPal[16];

#endif // GRIT_HEALTH_AND_SAFETY_TEXT_3_BN_GFX_H

//}}BLOCK(health_and_safety_text_3_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item health_and_safety_text_3(sprite_shape_size(sprite_shape::TALL, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(health_and_safety_text_3_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(health_and_safety_text_3_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

