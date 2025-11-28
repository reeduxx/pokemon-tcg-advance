#ifndef BN_SPRITE_ITEMS_TCG_LEFT_H
#define BN_SPRITE_ITEMS_TCG_LEFT_H

#include "bn_sprite_item.h"

//{{BLOCK(tcg_left_bn_gfx)

//======================================================================
//
//	tcg_left_bn_gfx, 64x32@4, 
//	+ palette 16 entries, not compressed
//	+ 32 tiles Metatiled by 8x4 not compressed
//	Total size: 32 + 1024 = 1056
//
//	Time-stamp: 2025-11-27, 19:19:10
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TCG_LEFT_BN_GFX_H
#define GRIT_TCG_LEFT_BN_GFX_H

#define tcg_left_bn_gfxTilesLen 1024
extern const bn::tile tcg_left_bn_gfxTiles[32];

#define tcg_left_bn_gfxPalLen 32
extern const bn::color tcg_left_bn_gfxPal[16];

#endif // GRIT_TCG_LEFT_BN_GFX_H

//}}BLOCK(tcg_left_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item tcg_left(sprite_shape_size(sprite_shape::WIDE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(tcg_left_bn_gfxTiles, 32), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(tcg_left_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

