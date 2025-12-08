#pragma once

#include "bn_string.h"
#include "bn_string_view.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_vector.h"

class Typewriter {
    public:
        static constexpr int default_frames_per_char = 2;
        static constexpr int max_script_chars = 256;
        static constexpr int max_line_chars = 64;
        static constexpr int max_sprites = 64;

        Typewriter(bn::sprite_text_generator& text_generator, int x, int y, int frames_per_char = default_frames_per_char);
        void show(bn::string_view script);
        void update();
        [[nodiscard]] bool active() const {
            return _state != State::Inactive;
        }
        [[nodiscard]] bool finished_all() const {
            return _state == State::Inactive && _script_index >= _script.size();
        }
        void set_frames_per_char(int frames_per_char);
    private:
        enum State {
            Inactive,
            Typing,
            WaitingForPage,
            WaitingForWait,
            WaitingForClose
        };

        bn::sprite_text_generator& _text_generator;
        bn::vector<bn::sprite_ptr, max_sprites> _sprites;
        bn::string<max_script_chars> _script;
        int _script_index = 0;
        bn::string<max_line_chars> _line_text[2];
        int _current_line = 0;
        int _x = 0;
        int _y = 0;
        int _frames_per_char = default_frames_per_char;
        int _counter = 0;
        State _state = State::Inactive;
        void _clear_lines();
        void _clear_sprites();
        void _rebuild_sprites();
        void _step_one_token();
        void _skip_current_page();
};