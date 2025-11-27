#ifndef BN_REGULAR_BG_TILES_ITEMS_MENU_STYLE_0_H
#define BN_REGULAR_BG_TILES_ITEMS_MENU_STYLE_0_H

#include "bn_regular_bg_tiles_item.h"
#include "bn_bg_palette_item.h"

//{{BLOCK(menu_style_0_bn_gfx)

//======================================================================
//
//	menu_style_0_bn_gfx, 80x8@4, 
//	+ palette 16 entries, not compressed
//	+ 10 tiles not compressed
//	Total size: 32 + 320 = 352
//
//	Time-stamp: 2025-11-23, 00:56:21
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MENU_STYLE_0_BN_GFX_H
#define GRIT_MENU_STYLE_0_BN_GFX_H

#define menu_style_0_bn_gfxTilesLen 320
extern const bn::tile menu_style_0_bn_gfxTiles[10];

#define menu_style_0_bn_gfxPalLen 32
extern const bn::color menu_style_0_bn_gfxPal[16];

#endif // GRIT_MENU_STYLE_0_BN_GFX_H

//}}BLOCK(menu_style_0_bn_gfx)

namespace bn::regular_bg_tiles_items
{
    constexpr inline regular_bg_tiles_item menu_style_0(
            span<const tile>(menu_style_0_bn_gfxTiles, 10), bpp_mode::BPP_4, compression_type::NONE);

    constexpr inline bg_palette_item menu_style_0_palette(span<const color>(menu_style_0_bn_gfxPal, 16), 
            bpp_mode::BPP_4, compression_type::NONE);
}

#endif

