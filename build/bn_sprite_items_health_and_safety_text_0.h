#ifndef BN_SPRITE_ITEMS_HEALTH_AND_SAFETY_TEXT_0_H
#define BN_SPRITE_ITEMS_HEALTH_AND_SAFETY_TEXT_0_H

#include "bn_sprite_item.h"

//{{BLOCK(health_and_safety_text_0_bn_gfx)

//======================================================================
//
//	health_and_safety_text_0_bn_gfx, 64x32@4, 
//	+ palette 16 entries, not compressed
//	+ 32 tiles Metatiled by 8x4 not compressed
//	Total size: 32 + 1024 = 1056
//
//	Time-stamp: 2025-11-27, 19:19:10
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_HEALTH_AND_SAFETY_TEXT_0_BN_GFX_H
#define GRIT_HEALTH_AND_SAFETY_TEXT_0_BN_GFX_H

#define health_and_safety_text_0_bn_gfxTilesLen 1024
extern const bn::tile health_and_safety_text_0_bn_gfxTiles[32];

#define health_and_safety_text_0_bn_gfxPalLen 32
extern const bn::color health_and_safety_text_0_bn_gfxPal[16];

#endif // GRIT_HEALTH_AND_SAFETY_TEXT_0_BN_GFX_H

//}}BLOCK(health_and_safety_text_0_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item health_and_safety_text_0(sprite_shape_size(sprite_shape::WIDE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(health_and_safety_text_0_bn_gfxTiles, 32), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(health_and_safety_text_0_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

