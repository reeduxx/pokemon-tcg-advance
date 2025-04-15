#ifndef GUARD_DIALOGUE_BOX_H
#define GUARD_DIALOGUE_BOX_H

#include "bn_regular_bg_tiles_item.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_vector.h"
#include "ui_box.h"

class DialogueBox : public UIBox {
private:
    bn::sprite_text_generator& m_text_gen;
    bn::vector<bn::sprite_ptr, 32> m_text_sprites;
    bn::string<128> m_text;
    int m_chars_shown;
    int m_frame_counter;

public:
    DialogueBox(int x, int y, int width, int height, const bn::regular_bg_tiles_item& tiles_item, const bn::bg_palette_item& palette_item, bn::sprite_text_generator& text_gen);
    void update() override;
    void set_text(const bn::string<128>& text);
};

#endif // GUARD_DIALOGUE_BOX_H
