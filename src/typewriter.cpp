#include "typewriter.h"

#include "bn_keypad.h"
#include "bn_size.h"
#include "bn_utf8_character.h"
#include "bn_sprite_items_down_arrow.h"

Typewriter::Typewriter(bn::sprite_text_generator& text_generator, int x, int y, int frames_per_char) : _text_generator(text_generator), _x(x), _y(y), _frames_per_char(frames_per_char <= 0 ? 1 : frames_per_char) {}

void Typewriter::set_frames_per_char(int frames_per_char) {
    _frames_per_char = (frames_per_char <= 0) ? 1 : frames_per_char;
}

void Typewriter::show(bn::string_view script) {
    _script.clear();

    for(char c : script) {
        if(_script.full()) {
            break;
        }

        _script.push_back(c);
    }

    _script_index = 0;
    _counter = 0;
    _state = State::Typing;
    _clear_lines();
    _clear_sprites();
}

void Typewriter::_clear_lines() {
    _line_text[0].clear();
    _line_text[1].clear();
    _current_line = 0;
}

void Typewriter::_clear_sprites() {
    for(bn::sprite_ptr& s : _sprites) {
        s.set_visible(false);
    }

    _sprites.clear();
}

void Typewriter::_rebuild_sprites() {
    _sprites.clear();

    if(!_line_text[0].empty()) {
        _text_generator.generate(_x, _y, _line_text[0], _sprites);
    }

    if(!_line_text[1].empty()) {
        int second_line_y = _y + 16;
        _text_generator.generate(_x, second_line_y, _line_text[1], _sprites);
    }
}

void Typewriter::_step_one_token() {
    if(_script_index >= _script.size()) {
        _state = State::WaitingForClose;
        return;
    }

    char c = _script[_script_index];

    if(c == '\n') {
        ++_script_index;

        if(_current_line == 0) {
            _current_line = 1;
        } else {
            _state = State::WaitingForPage;
        }

        return;
    }

    if(c == '\f') {
        ++_script_index;
        _state = State::WaitingForPage;
        return;
    }

    if(c == '\v') {
        ++_script_index;
        _state = State::WaitingForWait;
        return;
    }

    unsigned char uc = static_cast<unsigned char>(c);

    if(uc & 0x80) {
        bn::utf8_character utf_c(_script[_script_index]);
        int char_size = utf_c.size();

        if(_current_line < 2) {
            for(int i = 0; i < char_size; ++i) {
                if(_line_text[_current_line].full()) {
                    _state = State::WaitingForPage;
                    return;
                }

                _line_text[_current_line].push_back(_script[_script_index + i]);
            }

            _script_index += char_size;
            _rebuild_sprites();
        } else {
            _state = State::WaitingForPage;
        }
    } else {
        if(_current_line < 2) {
            if(!_line_text[_current_line].full()) {
                _line_text[_current_line].push_back(c);
            } else {
                _state = State::WaitingForPage;
                return;
            }

            ++_script_index;
            _rebuild_sprites();
        } else {
            _state = State::WaitingForPage;
        }
    }
}

void Typewriter::update() {
    if(_state == State::Inactive) {
        return;
    }

    if(_state == State::Typing) {
        _destroy_arrow();
        int effective_frames_per_char = _frames_per_char;

        if(bn::keypad::a_pressed() || bn::keypad::b_held()) {
            effective_frames_per_char = 1;
        }

        _counter++;

        if(_counter >= effective_frames_per_char) {
            _counter = 0;
            _step_one_token();
        }
    } else if(_state == State::WaitingForPage) {
        _create_arrow();

        if(_arrow_action) {
            _arrow_action->update();
        }

        if(bn::keypad::a_pressed()) {
            _clear_lines();
            _clear_sprites();
            _destroy_arrow();
            _state = State::Typing;
        }
    } else if(_state == State::WaitingForWait) {
        _destroy_arrow();

        if(bn::keypad::a_pressed()) {
            _state = State::Typing;
        }
    } else if(_state == State::WaitingForClose) {
        if(bn::keypad::a_pressed()) {
            _clear_lines();
            _clear_sprites();
            _state = State::Inactive;
        }
    }
}

void Typewriter::_create_arrow() {
    if(_arrow) return;
    
    int arrow_x = 0;
    int arrow_y = 0;

    if(!_line_text[1].empty() && !_sprites.empty()) {
        arrow_x = _x + _text_generator.width(_line_text[1]) + 3;
        arrow_y = static_cast<int>(_sprites.back().y()) - 2;
    }

    _arrow = bn::sprite_items::down_arrow.create_sprite(arrow_x, arrow_y);
    _arrow_action = bn::create_sprite_animate_action_forever(*_arrow, 9, bn::sprite_items::down_arrow.tiles_item(), 0, 1, 2, 1);
}

void Typewriter::_destroy_arrow() {
    _arrow_action.reset();
    _arrow.reset();
}