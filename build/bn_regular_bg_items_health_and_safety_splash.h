#ifndef BN_REGULAR_BG_ITEMS_HEALTH_AND_SAFETY_SPLASH_H
#define BN_REGULAR_BG_ITEMS_HEALTH_AND_SAFETY_SPLASH_H

#include "bn_regular_bg_item.h"

//{{BLOCK(health_and_safety_splash_bn_gfx)

//======================================================================
//
//	health_and_safety_splash_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 301 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 9632 + 2048 = 11712
//
//	Time-stamp: 2025-11-23, 00:22:20
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_HEALTH_AND_SAFETY_SPLASH_BN_GFX_H
#define GRIT_HEALTH_AND_SAFETY_SPLASH_BN_GFX_H

#define health_and_safety_splash_bn_gfxTilesLen 9632
extern const bn::tile health_and_safety_splash_bn_gfxTiles[301];

#define health_and_safety_splash_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell health_and_safety_splash_bn_gfxMap[1024];

#define health_and_safety_splash_bn_gfxPalLen 32
extern const bn::color health_and_safety_splash_bn_gfxPal[16];

#endif // GRIT_HEALTH_AND_SAFETY_SPLASH_BN_GFX_H

//}}BLOCK(health_and_safety_splash_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item health_and_safety_splash(
            regular_bg_tiles_item(span<const tile>(health_and_safety_splash_bn_gfxTiles, 301), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(health_and_safety_splash_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(health_and_safety_splash_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

