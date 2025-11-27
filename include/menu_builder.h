#pragma once

#include "bn_bg_palette_item.h"
#include "bn_optional.h"
#include "bn_regular_bg_map_cell.h"
#include "bn_regular_bg_map_item.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_tiles_item.h"

class MenuBuilder {
    public:
        static constexpr int cols = 32;
        static constexpr int rows = 32;
        MenuBuilder(const bn::regular_bg_tiles_item& tiles, const bn::bg_palette_item& pal);
        void reset();
        void draw(int x, int y, int w, int h);
        [[nodiscard]] bn::regular_bg_ptr create_bg();
        [[nodiscard]] bn::regular_bg_map_ptr bg_map() const;
    private:
        struct MapData {
            alignas(int) bn::regular_bg_map_cell cells[cols * rows];
            bn::regular_bg_map_item map_item;
            MapData();
            void clear();
        };

        MapData _map_data;
        const bn::regular_bg_tiles_item* _tiles;
        const bn::bg_palette_item* _pal;
        bn::optional<bn::regular_bg_ptr> _bg;
        void _set_cell(int x, int y, int tile_idx);
};