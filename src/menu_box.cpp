#include "menu_box.h"

MenuBox::MenuBox(int x, int y, int width, int height, const bn::regular_bg_tiles_item& tiles_item, const bn::bg_palette_item& palette_item, bn::sprite_text_generator& text_gen) :
    UIBox(x, y, width, height, tiles_item, palette_item), m_text_gen(text_gen), m_cursor_index(0) {}

void MenuBox::update() {
    m_option_sprites.clear();
    int y_offset = 0;

    for(int i = 0; i < m_options.size(); ++i) {
        bn::string<32> text = (i == m_cursor_index ? "> " : "  ") + m_options[i];
        m_text_gen.generate((m_x + 1) * 8, (m_y + 1 + y_offset++) * 8, text, m_option_sprites);
    }
}

void MenuBox::set_options(const bn::vector<bn::string<32>, 8>& options) {
    m_options = options;
    update();
}

void MenuBox::move_cursor(int delta) {
    m_cursor_index += delta;
    if(m_cursor_index < 0)
        m_cursor_index = m_options.size() - 1;
    if(m_cursor_index >= m_options.size())
        m_cursor_index = 0;
    update();
}

int MenuBox::selected_index() const {
    return m_cursor_index;
}
