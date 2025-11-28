#ifndef BN_SPRITE_ITEMS_ENERGY_SHEET_3_H
#define BN_SPRITE_ITEMS_ENERGY_SHEET_3_H

#include "bn_sprite_item.h"

//{{BLOCK(energy_sheet_3_bn_gfx)

//======================================================================
//
//	energy_sheet_3_bn_gfx, 32x32@4, 
//	+ palette 16 entries, not compressed
//	+ 16 tiles Metatiled by 4x4 not compressed
//	Total size: 32 + 512 = 544
//
//	Time-stamp: 2025-11-27, 19:19:10
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ENERGY_SHEET_3_BN_GFX_H
#define GRIT_ENERGY_SHEET_3_BN_GFX_H

#define energy_sheet_3_bn_gfxTilesLen 512
extern const bn::tile energy_sheet_3_bn_gfxTiles[16];

#define energy_sheet_3_bn_gfxPalLen 32
extern const bn::color energy_sheet_3_bn_gfxPal[16];

#endif // GRIT_ENERGY_SHEET_3_BN_GFX_H

//}}BLOCK(energy_sheet_3_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item energy_sheet_3(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(energy_sheet_3_bn_gfxTiles, 16), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(energy_sheet_3_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

