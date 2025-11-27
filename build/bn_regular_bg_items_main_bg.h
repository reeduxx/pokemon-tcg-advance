#ifndef BN_REGULAR_BG_ITEMS_MAIN_BG_H
#define BN_REGULAR_BG_ITEMS_MAIN_BG_H

#include "bn_regular_bg_item.h"

//{{BLOCK(main_bg_bn_gfx)

//======================================================================
//
//	main_bg_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 2 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 64 + 2048 = 2144
//
//	Time-stamp: 2025-11-25, 00:30:14
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAIN_BG_BN_GFX_H
#define GRIT_MAIN_BG_BN_GFX_H

#define main_bg_bn_gfxTilesLen 64
extern const bn::tile main_bg_bn_gfxTiles[2];

#define main_bg_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell main_bg_bn_gfxMap[1024];

#define main_bg_bn_gfxPalLen 32
extern const bn::color main_bg_bn_gfxPal[16];

#endif // GRIT_MAIN_BG_BN_GFX_H

//}}BLOCK(main_bg_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item main_bg(
            regular_bg_tiles_item(span<const tile>(main_bg_bn_gfxTiles, 2), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(main_bg_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(main_bg_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

