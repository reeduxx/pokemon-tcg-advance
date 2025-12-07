#include "dialogue.h"

#include "bn_keypad.h"

Dialogue::Dialogue(bn::sprite_text_generator& text_generator, int x, int y) : _text_generator(text_generator), _x(x), _y(y) {}

void Dialogue::show(const bn::string<256>& text) {
    _full_text = text;
    _visible_chars = 0;
    _frame_counter = 0;
    _state = State::Typing;
    _clear_sprites();
    _rebuild_sprites();
}

void Dialogue::update() {
    if(_state == State::Inactive) {
        return;
    }

    int effective_frames_per_char = _frames_per_char;

    if(bn::keypad::b_held()) {
        effective_frames_per_char = 1;
    }

    if(_state == State::Typing) {
        if(bn::keypad::a_pressed() || bn::keypad::b_pressed()) {
            skip_typewriter();
            _state = State::Done;
            return;
        }

        _frame_counter++;

        if(_frame_counter >= effective_frames_per_char) {
            _frame_counter = 0;

            if(_visible_chars < _full_text.size()) {
                ++_visible_chars;
                _rebuild_sprites();
            }

            if(_visible_chars >= _full_text.size()) {
                _state = State::Done;
            }
        }
    } else if(_state == State::Done) {
        if(bn::keypad::a_pressed()) {
            _clear_sprites();
            _state = State::Inactive;
        }
    }
}

void Dialogue::skip_typewriter() {
    if(_state == State::Inactive) {
        return;
    }

    _visible_chars = _full_text.size();
    _rebuild_sprites();
}

void Dialogue::_rebuild_sprites() {
    _sprites.clear();

    if(_visible_chars == 0 || _full_text.empty()) {
        return;
    }

    bn::string<256> visible;

    for(int i = 0; i < _visible_chars && i < _full_text.size(); ++i) {
        visible.push_back(_full_text[i]);
    }

    _text_generator.generate(_x, _y, visible, _sprites);
}

void Dialogue::_clear_sprites() {
    for(bn::sprite_ptr& sprite : _sprites) {
        sprite.set_visible(false);
    }

    _sprites.clear();
}