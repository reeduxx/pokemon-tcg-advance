#include "ui_box.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_regular_bg_item.h"

enum class BorderTile {
    TOP_LEFT = 1,
    TOP = 2,
    TOP_RIGHT = 3,
    LEFT = 4,
    CENTER = 5,
    RIGHT = 6,
    BOTTOM_LEFT = 7,
    BOTTOM = 8,
    BOTTOM_RIGHT = 9
};

UIBox::UIBox(int x, int y, int width, int height, const bn::regular_bg_tiles_item& tiles_item, const bn::bg_palette_item& palette_item) :
    m_x(x), m_y(y), m_width(width), m_height(height),
    m_tiles_item(tiles_item),
    m_map_item(m_cells[0], bn::size(map_cols, map_rows))
{
    // Fill with center tiles
    for(int i = 0; i < map_cols * map_rows; ++i) {
        bn::regular_bg_map_cell_info info(m_cells[i]);
        info.set_tile_index(static_cast<int>(BorderTile::CENTER));
        m_cells[i] = info.cell();
    }

    // Construct bg_item and create both bg_ptr and bg_map_ptr
    bn::regular_bg_item bg_item(m_tiles_item, palette_item, m_map_item);
    m_bg_ptr = bn::regular_bg_ptr::create(m_x * 8, m_y * 8, bg_item);
    m_bg_map_ptr = m_bg_ptr->map();

    draw_border();
    m_bg_map_ptr->reload_cells_ref();
}

void UIBox::update() {}

void UIBox::show() {
    if(m_bg_ptr) m_bg_ptr->set_visible(true);
}

void UIBox::hide() {
    if(m_bg_ptr) m_bg_ptr->set_visible(false);
}

void UIBox::draw_border() {
    for(int row = 0; row < m_height; ++row) {
        for(int col = 0; col < m_width; ++col) {
            BorderTile tile;

            if(row == 0) {
                if(col == 0) tile = BorderTile::TOP_LEFT;
                else if(col == m_width - 1) tile = BorderTile::TOP_RIGHT;
                else tile = BorderTile::TOP;
            }
            else if(row == m_height - 1) {
                if(col == 0) tile = BorderTile::BOTTOM_LEFT;
                else if(col == m_width - 1) tile = BorderTile::BOTTOM_RIGHT;
                else tile = BorderTile::BOTTOM;
            }
            else {
                if(col == 0) tile = BorderTile::LEFT;
                else if(col == m_width - 1) tile = BorderTile::RIGHT;
                else tile = BorderTile::CENTER;
            }

            int cell_x = m_x + col;
            int cell_y = m_y + row;
            int index = m_map_item.cell_index(cell_x, cell_y);
            bn::regular_bg_map_cell_info info(m_cells[index]);
            info.set_tile_index(static_cast<int>(tile));
            m_cells[index] = info.cell();
        }
    }

    m_bg_map_ptr->reload_cells_ref(); // ✅ This is now valid
}
