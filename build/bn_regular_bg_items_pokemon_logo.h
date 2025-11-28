#ifndef BN_REGULAR_BG_ITEMS_POKEMON_LOGO_H
#define BN_REGULAR_BG_ITEMS_POKEMON_LOGO_H

#include "bn_regular_bg_item.h"

//{{BLOCK(pokemon_logo_bn_gfx)

//======================================================================
//
//	pokemon_logo_bn_gfx, 256x256@8, 
//	+ palette 160 entries, not compressed
//	+ 121 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 320 + 7744 + 2048 = 10112
//
//	Time-stamp: 2025-11-27, 19:19:10
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_POKEMON_LOGO_BN_GFX_H
#define GRIT_POKEMON_LOGO_BN_GFX_H

#define pokemon_logo_bn_gfxTilesLen 7744
extern const bn::tile pokemon_logo_bn_gfxTiles[242];

#define pokemon_logo_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell pokemon_logo_bn_gfxMap[1024];

#define pokemon_logo_bn_gfxPalLen 320
extern const bn::color pokemon_logo_bn_gfxPal[160];

#endif // GRIT_POKEMON_LOGO_BN_GFX_H

//}}BLOCK(pokemon_logo_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item pokemon_logo(
            regular_bg_tiles_item(span<const tile>(pokemon_logo_bn_gfxTiles, 242), bpp_mode::BPP_8, compression_type::NONE), 
            bg_palette_item(span<const color>(pokemon_logo_bn_gfxPal, 160), bpp_mode::BPP_8, compression_type::NONE),
            regular_bg_map_item(pokemon_logo_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

