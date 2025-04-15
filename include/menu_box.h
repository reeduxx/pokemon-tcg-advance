#ifndef GUARD_MENU_BOX_H
#define GUARD_MENU_BOX_H

#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_vector.h"
#include "ui_box.h"

class MenuBox : public UIBox {
private:
    bn::sprite_text_generator& m_text_gen;
    bn::vector<bn::sprite_ptr, 64> m_option_sprites;
    bn::vector<bn::string<32>, 8> m_options;
    int m_cursor_index;

public:
    MenuBox(int x, int y, int width, int height, const bn::regular_bg_tiles_item& tiles_item, const bn::bg_palette_item& palette_item, bn::sprite_text_generator& text_gen);
    void update() override;
    void set_options(const bn::vector<bn::string<32>, 8>& options);
    void move_cursor(int delta);
    int selected_index() const;
};

#endif // GUARD_MENU_BOX_H
