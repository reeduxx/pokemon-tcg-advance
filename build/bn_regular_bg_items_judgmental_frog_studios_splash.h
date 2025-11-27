#ifndef BN_REGULAR_BG_ITEMS_JUDGMENTAL_FROG_STUDIOS_SPLASH_H
#define BN_REGULAR_BG_ITEMS_JUDGMENTAL_FROG_STUDIOS_SPLASH_H

#include "bn_regular_bg_item.h"

//{{BLOCK(judgmental_frog_studios_splash_bn_gfx)

//======================================================================
//
//	judgmental_frog_studios_splash_bn_gfx, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 178 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 11392 + 2048 = 13952
//
//	Time-stamp: 2025-11-23, 00:22:20
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_JUDGMENTAL_FROG_STUDIOS_SPLASH_BN_GFX_H
#define GRIT_JUDGMENTAL_FROG_STUDIOS_SPLASH_BN_GFX_H

#define judgmental_frog_studios_splash_bn_gfxTilesLen 11392
extern const bn::tile judgmental_frog_studios_splash_bn_gfxTiles[356];

#define judgmental_frog_studios_splash_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell judgmental_frog_studios_splash_bn_gfxMap[1024];

#define judgmental_frog_studios_splash_bn_gfxPalLen 512
extern const bn::color judgmental_frog_studios_splash_bn_gfxPal[256];

#endif // GRIT_JUDGMENTAL_FROG_STUDIOS_SPLASH_BN_GFX_H

//}}BLOCK(judgmental_frog_studios_splash_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item judgmental_frog_studios_splash(
            regular_bg_tiles_item(span<const tile>(judgmental_frog_studios_splash_bn_gfxTiles, 356), bpp_mode::BPP_8, compression_type::NONE), 
            bg_palette_item(span<const color>(judgmental_frog_studios_splash_bn_gfxPal, 256), bpp_mode::BPP_8, compression_type::NONE),
            regular_bg_map_item(judgmental_frog_studios_splash_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

