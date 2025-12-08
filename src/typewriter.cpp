#include "typewriter.h"

#include "bn_keypad.h"

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
        int second_line_y = _y + 14;
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

    if(c == '[' && (_script_index + 2) < _script.size() && _script[_script_index + 2] == ']') {
        char code = _script[_script_index + 1];

        if(code == 'P') {
            _script_index += 3;
            _state = State::WaitingForPage;
            return;
        } else if(code == 'W') {
            _script_index += 3;
            _state = State::WaitingForWait;
            return;
        }
    }

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

void Typewriter::_skip_current_page() {
    if(_state != State::Typing && _state != State::WaitingForWait) {
        return;
    }

    if(_state == State::WaitingForWait) {
        _state = State::Typing;
    }

    while(_state == State::Typing && _script_index < _script.size()) {
        _step_one_token();

        if(_state == State::WaitingForPage || _state == State::WaitingForClose) {
            break;
        }

        if(_state == State::WaitingForWait) {
            _state = State::Typing;
        }
    }
}

void Typewriter::update() {
    if(_state == State::Inactive) {
        return;
    }

    int effective_frames_per_char = _frames_per_char;

    if(bn::keypad::b_held()) {
        effective_frames_per_char = 1;
    }

    if(_state == State::Typing) {
        if(bn::keypad::a_pressed() || bn::keypad::b_pressed()) {
            _skip_current_page();
            return;
        }

        _counter++;

        if(_counter >= effective_frames_per_char) {
            _counter = 0;
            _step_one_token();
        }
    } else if(_state == State::WaitingForPage) {
        if(bn::keypad::a_pressed()) {
            _clear_lines();
            _clear_sprites();
            _state = State::Typing;
        }
    } else if(_state == State::WaitingForWait) {
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