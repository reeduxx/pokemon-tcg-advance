#include "bg_builder.h"
#include "bn_memory.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_map_cell_info.h"

BgBuilder::MapData::MapData() : map_item(cells[0], bn::size(BgBuilder::cols, BgBuilder::rows)) {
    clear();
}

void BgBuilder::MapData::clear() {
    bn::memory::clear(cells);
}

BgBuilder::BgBuilder(const bn::regular_bg_tiles_item& tiles, const bn::bg_palette_item& pal) : _tiles(&tiles), _pal(&pal) {
    _map_data.clear();
}

void BgBuilder::reset() {
    _map_data.clear();
    _bg.reset();
}

void BgBuilder::_set_cell(int x, int y, int tile_idx) {
    if(x < 0 || x >= cols || y < 0 || y >= rows) {
        return;
    }

    auto& cell = _map_data.cells[_map_data.map_item.cell_index(x, y)];
    bn::regular_bg_map_cell_info info(cell);
    info.set_tile_index(tile_idx);
    cell = info.cell();
}

void BgBuilder::draw(int x, int y, int w, int h) {
    if(w < 2 || h < 2) {
        return;
    }

    constexpr int TL = 1;
    constexpr int T = 2;
    constexpr int TR = 3;
    constexpr int L = 4;
    constexpr int F = 5;
    constexpr int R = 6;
    constexpr int BL = 7;
    constexpr int B = 8;
    constexpr int BR = 9;

    _set_cell(x, y, TL);
    _set_cell(x + w - 1, y, TR);
    _set_cell(x, y + h - 1, BL);
    _set_cell(x + w - 1, y + h - 1, BR);

    for(int cx = x + 1; cx < x + w - 1; ++cx) {
        _set_cell(cx, y, T);
        _set_cell(cx, y + h - 1, B);
    }

    for(int cy = y + 1; cy < y + h - 1; ++cy) {
        _set_cell(x, cy, L);
        _set_cell(x + w - 1, cy, R);

        for(int cx = x + 1; cx < x + w - 1; ++cx) {
            _set_cell(cx, cy, F);
        }
    }
}

bn::regular_bg_ptr BgBuilder::create_bg() {
    bn::regular_bg_item bg_item(*_tiles, *_pal, _map_data.map_item);
    _bg = bg_item.create_bg(0, 0);
    return *_bg;
}

bn::regular_bg_map_ptr BgBuilder::bg_map() const {
    return _bg->map();
}

const bn::regular_bg_map_item& BgBuilder::map_item() const {
    return _map_data.map_item;
}