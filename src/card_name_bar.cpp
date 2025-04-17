#include "card_name_bar.h"

CardNameBar::CardNameBar(const bn::regular_bg_item& bg, bn::sprite_text_generator& text_generator) : m_bg(bg.create_bg(0, -48)), m_text_generator(text_generator) {
    show();
}

void CardNameBar::update() {}

void CardNameBar::set_text(const bn::string<32>& text) {
    if(text != m_text) {
        m_text = text;
        m_text_sprites.clear();
        m_text_generator.generate(-108, 72, m_text, m_text_sprites);
    }
}

void CardNameBar::clear() {
    m_text.clear();
    m_text_sprites.clear();
}

void CardNameBar::show() {
    m_bg.set_visible(true);

    for(auto& sprite : m_text_sprites) {
        sprite.set_visible(true);
    }
}

void CardNameBar::hide() {
    m_bg.set_visible(false);

    for(auto& sprite : m_text_sprites) {
        sprite.set_visible(false);
    }
}