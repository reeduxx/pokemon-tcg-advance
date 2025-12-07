#pragma once

#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_vector.h"

class Dialogue {
    public:
        Dialogue(bn::sprite_text_generator& text_generator, int x, int y);
        void show(const bn::string<256>& text);
        void update();
        
        [[nodiscard]] bool active() const {
            return _state != State::Inactive;
        }

        [[nodiscard]] bool finished() const {
            return _state != State::Done;
        }

        [[nodiscard]] bool finished_and_closed() const {
            return _state == State::Inactive;
        }

        void skip_typewriter();
        void set_frames_per_char(int frames) {
            _frames_per_char = (frames <= 0) ? 1 : frames;
        }
    private:
        enum class State {
            Inactive,
            Typing,
            Done
        };

        bn::sprite_text_generator& _text_generator;
        bn::vector<bn::sprite_ptr, 64> _sprites;
        bn::string<256> _full_text;
        int _visible_chars = 0;
        int _frames_per_char = 2;
        int _frame_counter = 0;
        int _x;
        int _y;
        State _state = State::Inactive;
        void _rebuild_sprites();
        void _clear_sprites();
};