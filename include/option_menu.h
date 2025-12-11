#pragma once

#include "bn_optional.h"
#include "bn_rect_window.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_vector.h"
#include "bg_builder.h"

class OptionMenu {
    public:
        OptionMenu();
        bool update();
    private:
        enum class State {
            FadeIn,
            WaitInput,
            FadeOut,
            Done
        };

        struct OptionEntry {
            bn::string<20> name;
            bn::vector<bn::string<7>, 15> values;
            int current_idx = 0;
        };

        bn::optional<bn::regular_bg_ptr> _bg;
        bn::optional<bn::regular_bg_ptr> _option_bg;
        bn::optional<bn::rect_window> _selection_window;
        BgBuilder _bg_builder;
        bn::sprite_text_generator _text_generator;
        bn::vector<OptionEntry, 3> _options;
        int _selected_option = 0;
        bn::vector<bn::sprite_ptr, 32> _label_sprites;
        bn::vector<bn::sprite_ptr, 32> _value_sprites;
        State _state = State::FadeIn;
        int _timer = 0;
        void _load_options();
        void _update_fade_in();
        void _handle_input();
        void _update_fade_out();
        void _build_bg();
        void _build_text();
        void _update_option_text();
        void _update_selection();
};