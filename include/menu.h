#ifndef GUARD_MENU_H
#define GUARD_MENU_H

#include "bn_bg_palette_item.h"
#include "bn_fixed_point.h"
#include "bn_optional.h"
#include "bn_regular_bg_map_cell.h"
#include "bn_regular_bg_map_item.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_tiles_item.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_vector.h"

class Menu {
    private:
        int m_x, m_y, m_width, m_height;
        static constexpr int map_cols = 32;
        static constexpr int map_rows = 32;
        bn::regular_bg_map_cell m_cells[map_cols * map_rows];
        bn::sprite_text_generator m_text_generator;
        bn::regular_bg_map_item m_map_item;
        bn::regular_bg_tiles_item m_tiles_item;
        bn::optional<bn::regular_bg_map_ptr> m_bg_map_ptr;
        bn::optional<bn::regular_bg_ptr> m_bg_ptr;
        bn::vector<bn::string<24>, 6> m_options;
        bn::vector<bn::sprite_ptr, 32> m_option_text_sprites;
        int m_selected_index = 0;
        bool m_visible = false;
    public:
        Menu(int x, int y, int width, int height, const bn::regular_bg_tiles_item& tiles_item, const bn::bg_palette_item& palette_item, bn::sprite_text_generator& text_generator);
        void set_options(const bn::span<const::bn::string<24>>& options);
        void show();
        void hide();
        int option_count() const;
        bn::fixed_point option_pos(int i) const;
        void draw_text();
    private:
        void draw_border();
};

#endif // GUARD_MENU_H
