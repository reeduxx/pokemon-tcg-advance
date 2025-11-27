#ifndef BN_SPRITE_ITEMS_ENERGY_SHEET_1_H
#define BN_SPRITE_ITEMS_ENERGY_SHEET_1_H

#include "bn_sprite_item.h"

//{{BLOCK(energy_sheet_1_bn_gfx)

//======================================================================
//
//	energy_sheet_1_bn_gfx, 128x32@4, 
//	+ palette 16 entries, not compressed
//	+ 64 tiles Metatiled by 4x4 not compressed
//	Total size: 32 + 2048 = 2080
//
//	Time-stamp: 2025-11-23, 00:22:20
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ENERGY_SHEET_1_BN_GFX_H
#define GRIT_ENERGY_SHEET_1_BN_GFX_H

#define energy_sheet_1_bn_gfxTilesLen 2048
extern const bn::tile energy_sheet_1_bn_gfxTiles[64];

#define energy_sheet_1_bn_gfxPalLen 32
extern const bn::color energy_sheet_1_bn_gfxPal[16];

#endif // GRIT_ENERGY_SHEET_1_BN_GFX_H

//}}BLOCK(energy_sheet_1_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item energy_sheet_1(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(energy_sheet_1_bn_gfxTiles, 64), bpp_mode::BPP_4, compression_type::NONE, 4), 
            sprite_palette_item(span<const color>(energy_sheet_1_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

