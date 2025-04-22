#include "bn_log.h"
#include "menu.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_regular_bg_item.h"

enum class BorderTile {
    TOP_LEFT = 0,
    TOP = 1,
    TOP_RIGHT = 2,
    LEFT = 3,
    CENTER = 4,
    RIGHT = 5,
    BOTTOM_LEFT = 6,
    BOTTOM = 7,
    BOTTOM_RIGHT = 8,
    NONE = 9
};

Menu::Menu(int x, int y, int width, int height, const bn::regular_bg_tiles_item& tiles_item, const bn::bg_palette_item& palette_item, bn::sprite_text_generator& text_generator) :
    m_x(x), m_y(y), m_width(width), m_height(height), m_tiles_item(tiles_item), m_text_generator(text_generator), m_map_item(m_cells[0], bn::size(map_cols, map_rows)) {
    for(int i = 0; i < map_cols * map_rows; ++i) {
        bn::regular_bg_map_cell_info info(m_cells[i]);
        info.set_tile_index(static_cast<int>(BorderTile::NONE));
        m_cells[i] = info.cell();
    }

    bn::regular_bg_item bg_item(m_tiles_item, palette_item, m_map_item);
    m_bg_ptr = bn::regular_bg_ptr::create(m_x * 8, m_y * 8, bg_item);
    m_bg_map_ptr = m_bg_ptr->map();
    draw_border();
    m_bg_ptr->set_position(0, 48);
    m_bg_map_ptr->reload_cells_ref();
}

void Menu::set_options(const bn::span<const bn::string<24>>& options) {
    m_options.clear();
    int max_length = 0;

    for(const bn::string<24>& opt : options) {
        m_options.push_back(opt);
        max_length = bn::max(max_length, opt.size());
    }

    BN_LOG(max_length);
    m_width = max_length + 2;
    m_height = m_options.size() + 2;
    m_x = 31 - m_width;
    m_y = 17 - m_height;
    draw_border();
    draw_text();
}

void Menu::show() {
    m_visible = true;

    if(m_bg_ptr.has_value()) {
        m_bg_ptr->set_visible(true);
    }
    
    for(auto& sprite : m_option_text_sprites) {
        sprite.set_visible(true);
    }
}

void Menu::hide() {
    m_visible = false;
    if(m_bg_ptr.has_value()) {
        m_bg_ptr->set_visible(false);
    }

    for(auto& sprite : m_option_text_sprites) {
        sprite.set_visible(false);
    }
}

void Menu::draw_border() {
    for(int row = 0; row < map_rows; ++row) {
        for(int col = 0; col < map_cols; ++col) {
            int index = m_map_item.cell_index(col, row);
            bn::regular_bg_map_cell_info info(m_cells[index]);
            info.set_tile_index(static_cast<int>(BorderTile::NONE));
            m_cells[index] = info.cell();
        }
    }

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

    m_bg_map_ptr->reload_cells_ref();
}

void Menu::draw_text() {
    m_option_text_sprites.clear();

    for(int i = 0; i < m_options.size(); ++i) {
        int x = -120 + (m_x * 8);
        int y = -80 + (m_y + 1 + i) * 8;
        bn::string<24> text = m_options[i];
        m_text_generator.generate(x, y, text, m_option_text_sprites);
    }
}

int Menu::option_count() const {
    return m_options.size();
}

bn::fixed_point Menu::option_pos(int i) const {
    int x = m_x * 8 + 4;
    int y = (m_y + 1 + i) * 8 + 48;
    return bn::fixed_point(x, y);
}