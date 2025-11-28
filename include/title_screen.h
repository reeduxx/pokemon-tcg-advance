#pragma once

#include "bn_backdrop_color_hbe_ptr.h"
#include "bn_fixed.h"
#include "bn_optional.h"
#include "bn_regular_bg_actions.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

class TitleScreen {
    public:
        explicit TitleScreen();
        bool update();
    private:
        enum class State {
            FadeInLogo,
            FadeInTCG,
            LogoAnim,
            WaitInput,
            FadeOut,
            Done
        };

        struct Card {
            bn::sprite_ptr sprite;
            bn::fixed y;
            bn::fixed speed;
            int lane;
        };

        bn::optional<bn::regular_bg_ptr> _bg;
        State _state;
        int _timer;
        int _blink_timer;
        bool _blink_visible;
        bn::vector<bn::sprite_ptr, 2> _tcg_sprites;
        bn::vector<bn::sprite_ptr, 2> _press_start_sprites;
        bn::optional<bn::regular_bg_move_to_action> _logo_move_action;
        bn::optional<bn::sprite_move_to_action> _tcg_left_action;
        bn::optional<bn::sprite_move_to_action> _tcg_right_action;
        static constexpr int fade_duration = 60;
        static constexpr int anim_duration = 60;
        static constexpr int blink_interval = 20;
        bn::optional<bn::backdrop_color_hbe_ptr> _backdrop_color_hbe;
        int _gradient_phase = 0;
        int _gradient_timer = 0;
        bn::vector<Card, 8> _cards;

        void _load_bg();
        void _update_fade_in_logo();
        void _update_fade_in_tcg();
        void _update_logo_anim();
        void _update_wait_input();
        void _update_fade_out();
        void _update_press_text_blink();
        void _handle_input();
        void _skip();
        inline bn::fixed clamp_lerp(int time, int duration);
        void _init_cards();
        void _update_cards();
};