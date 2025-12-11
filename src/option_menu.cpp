#include "option_menu.h"

#include "bn_blending.h"
#include "bn_keypad.h"
#include "bn_regular_bg_items_main_bg.h"
#include "font.h"
#include "frame_styles.h"

namespace {
    constexpr int menu_left_tile = 2;
    constexpr int menu_width_tiles = 28;

    inline int tile_to_screen_x(int tile_x) {
        return -128 + tile_x * 8;
    }

    inline int tile_to_screen_y(int tile_y) {
        return -128 + tile_y * 8;
    }
}

OptionMenu::OptionMenu() : _bg_builder(frame_styles[0].tiles, frame_styles[0].pal), _text_generator(font::font) {
    _bg = bn::regular_bg_items::main_bg.create_bg(0, 0);
    _bg->set_blending_enabled(true);
    _load_options();
    _build_bg();
    _build_text();
}

bool OptionMenu::update() {
    switch(_state) {
        case State::FadeIn:
            _update_fade_in();
            break;
        case State::WaitInput:
            _handle_input();
            break;
        case State::FadeOut:
            _update_fade_out();
            break;
        case State::Done:
            return true;
        default:
            break;
    }

    return false;
}

void OptionMenu::_load_options() {
    {
        OptionEntry e;
        e.name = "TEXT SPEED";
        e.values.clear();
        e.values.push_back("SLOW");
        e.values.push_back("MID");
        e.values.push_back("FAST");
        e.current_idx = 1;
        _options.push_back(e);
    }

    {
        OptionEntry e;
        e.name = "FRAME";
        e.values.clear();
        e.values.push_back("TYPE 1");
        e.values.push_back("TYPE 2");
        e.current_idx = 0;
        _options.push_back(e);
    }

    {
        OptionEntry e;
        e.name = "CANCEL";
        e.values.clear();
        e.current_idx = 0;
        _options.push_back(e);
    }
}

void OptionMenu::_update_fade_in() {
    constexpr int fade_frames = 30;

    if(_timer >= fade_frames) {
        bn::blending::set_fade_alpha(0);
        _state = State::WaitInput;
        _timer = 0;
        return;
    }

    bn::fixed t = bn::fixed(_timer) / fade_frames;
    bn::fixed a = bn::fixed(1) - t;
    bn::blending::set_fade_alpha(a);
    ++_timer;
}

void OptionMenu::_handle_input() {
    if(bn::keypad::b_pressed()) {
        _state = State::FadeOut;
        return;
    }

    if(bn::keypad::up_pressed()) {
        _selected_option--;

        if(_selected_option < 0) {
            _selected_option = 0;
        } else {
            _update_option_text();
        }
    } else if(bn::keypad::down_pressed()) {
        _selected_option++;

        if(_selected_option >= _options.size()) {
            _selected_option = _options.size() - 1;
        } else {
            _update_option_text();
        }
    }

    OptionEntry& current_option = _options[_selected_option];

    if(!current_option.values.empty()) {
        if(bn::keypad::left_pressed()) {
            current_option.current_idx--;

            if(current_option.current_idx < 0) {
                current_option.current_idx = 0;
            } else {
                _update_option_text();
            }
        } else if(bn::keypad::right_pressed()) {
            current_option.current_idx++;

            if(current_option.current_idx >= current_option.values.size()) {
                current_option.current_idx = current_option.values.size() - 1;
            } else {
                _update_option_text();
            }
        }
    }
}

void OptionMenu::_update_fade_out() {
    constexpr int fade_frames = 30;

    if(_timer >= fade_frames) {
        bn::blending::set_fade_alpha(1);
        _state = State::Done;
        return;
    }

    bn::fixed t = bn::fixed(_timer) / fade_frames;
    bn::blending::set_fade_alpha(t);
    ++_timer;
}

void OptionMenu::_build_bg() {
    _bg_builder.reset();
    _bg_builder.draw(menu_left_tile, 6, menu_width_tiles, 4);
    _bg_builder.draw(menu_left_tile, 10, menu_width_tiles, 16);
    _option_bg.reset();
    _option_bg = _bg_builder.create_bg();
    _option_bg->set_blending_enabled(true);
}

void OptionMenu::_build_text() {
    _text_generator.generate(tile_to_screen_x(menu_left_tile + 2), tile_to_screen_y(7) + 8, "OPTION", _label_sprites);

    int next_y = 11;

    for(OptionEntry& e : _options) {
        _text_generator.generate(tile_to_screen_x(menu_left_tile + 2), tile_to_screen_y(next_y) + 8, e.name, _label_sprites);

        for(auto& s : _label_sprites) {
            s.set_blending_enabled(true);
        }

        if(!e.values.empty()) {
            _text_generator.generate(tile_to_screen_x(menu_left_tile + 16), tile_to_screen_y(next_y) + 8, e.values[e.current_idx], _value_sprites);

            for(auto& s : _value_sprites) {
                s.set_blending_enabled(true);
            }
        }

        next_y += 2;
    }
}

void OptionMenu::_update_option_text() {
    for(auto& s : _value_sprites) {
        s.set_visible(false);
    }

    _value_sprites.clear();

    int next_y = 11;

    for(OptionEntry& e : _options) {
        if(!e.values.empty()) {
            _text_generator.generate(tile_to_screen_x(menu_left_tile + 16), tile_to_screen_y(next_y) + 8, e.values[e.current_idx], _value_sprites);

            for(auto& s : _value_sprites) {
                s.set_blending_enabled(true);
            }
        }

        next_y += 2;
    }
}