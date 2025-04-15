#ifndef GUARD_UI_BOX_H
#define GUARD_UI_BOX_H

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_regular_bg_map_item.h"
#include "bn_regular_bg_tiles_item.h"
#include "bn_regular_bg_map_cell.h"
#include "bn_bg_palette_item.h"
#include "bn_optional.h"

class UIBox {
protected:
    int m_x, m_y, m_width, m_height;
    static constexpr int map_cols = 32;
    static constexpr int map_rows = 32;

    bn::regular_bg_map_cell m_cells[map_cols * map_rows];
    bn::regular_bg_map_item m_map_item;
    bn::regular_bg_tiles_item m_tiles_item;
    bn::optional<bn::regular_bg_map_ptr> m_bg_map_ptr;
    bn::optional<bn::regular_bg_ptr> m_bg_ptr;

public:
    UIBox(int x, int y, int width, int height, const bn::regular_bg_tiles_item& tiles_item, const bn::bg_palette_item& palette_item);
    virtual ~UIBox() = default;

    virtual void update();
    virtual void show();
    virtual void hide();
    virtual void draw_border();
};

#endif // GUARD_UI_BOX_H
