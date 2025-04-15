#include "dialogue_box.h"

DialogueBox::DialogueBox(int x, int y, int width, int height, const bn::regular_bg_tiles_item& tiles_item, const bn::bg_palette_item& palette_item, bn::sprite_text_generator& text_gen) :
    UIBox(x, y, width, height, tiles_item, palette_item), m_text_gen(text_gen), m_chars_shown(0), m_frame_counter(0) {}

void DialogueBox::update() {
    ++m_frame_counter;

    if((m_frame_counter & 3) == 0 && m_chars_shown < m_text.size()) {
        ++m_chars_shown;
        m_text_sprites.clear();
        bn::string<128> shown_text = m_text.substr(0, m_chars_shown);
        m_text_gen.generate((m_x + 1) * 8, (m_y + 1) * 8, shown_text, m_text_sprites);
    }
}

void DialogueBox::set_text(const bn::string<128>& text) {
    m_text = text;
    m_chars_shown = 0;
    m_frame_counter = 0;
    m_text_sprites.clear();
}
