#pragma once

#include "bn_optional.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

class Intro {
    public:
        explicit Intro();
        [[nodiscard]] bool update();
    private:
        struct Splash {
            bn::regular_bg_item bg;
            int fade_in_frames = 0;
            int hold_frames = 0;
            int fade_out_frames = 0;
            bool show_press_text = false;
        };

        enum class State {
            FadeIn,
            Hold,
            FadeOut,
            Done
        };

        void _load_current_splash();
        void _update_fade_in();
        void _update_hold();
        void _update_fade_out();
        void _update_press_text_blink();
        [[nodiscard]] bool _skip_requested() const;

        bn::vector<Splash, 4> _splashes;
        int _current_idx = 0;
        State _state = State::FadeIn;
        int _timer = 0;
        bn::optional<bn::regular_bg_ptr> _bg;
        bn::vector<bn::sprite_ptr, 4> _press_text_sprites;
        int _blink_timer = 0;
        bool _blink_visible = false;
};