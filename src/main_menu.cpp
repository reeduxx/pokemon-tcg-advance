#include "main_menu.h"
#include "bn_backdrop.h"
#include "bn_blending.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_sound_items.h"
#include "bn_time.h"
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

MainMenu::MainMenu() : _menu_builder(frame_styles[0].tiles, frame_styles[0].pal), _text_generator(font::font), _save_manager(SaveManager()), _state(State::FadeIn) {
    _build_entries(_save_manager->save_exists(), false);
    _bg = bn::regular_bg_items::main_bg.create_bg(0, 0);
    _options_bg = _menu_builder.create_bg();
    _build_text();
    _bg->set_blending_enabled(false);
    _options_bg->set_blending_enabled(true);
    bn::blending::set_fade_alpha(0.7);

    _selection_window = bn::rect_window::internal();
    _selection_window->set_show_blending(false);
    _selection_window->set_show_sprites(true);

    if(!_entries.empty()) {
        _selected_idx = 0;
        _update_selection();
    }
}

void MainMenu::_build_entries(bool has_save, bool ereader_enabled) {
    _entries.clear();
    int next_top = 6;

    if(has_save) {
        _menu_builder.draw(menu_left_tile, next_top, menu_width_tiles, 8);
        _entries.push_back(Entry { Choice::Continue, next_top, 8 });
        next_top += 8;
    }

    _menu_builder.draw(menu_left_tile, next_top, menu_width_tiles, 4);
    _entries.push_back(Entry { Choice::NewGame, next_top, 4 });
    next_top += 4;

    if(ereader_enabled) {
        _menu_builder.draw(menu_left_tile, next_top, menu_width_tiles, 4);
        _entries.push_back(Entry { Choice::EReader, next_top, 4 });
        next_top += 4;
    }

    _menu_builder.draw(menu_left_tile, next_top, menu_width_tiles, 4);
    _entries.push_back(Entry {Choice::Option, next_top, 4 });
}

void MainMenu::_update_selection() {
    BN_LOG("Updating");
    if(!_selection_window || _entries.empty()) {
        return;
    }

    const Entry& e = _entries[_selected_idx];
    const int top = tile_to_screen_y(e.top_tile);
    const int left = tile_to_screen_x(menu_left_tile);
    const int bottom = top + e.height_tiles * 8;
    const int right = left + menu_width_tiles * 8;
    _selection_window->set_boundaries(top, left, bottom, right);
}

bool MainMenu::update() {
    switch(_state) {
        case State::FadeIn:
            break;
        case State::WaitInput:
            _handle_input();
            break;
        case State::FadeOut:
            break;
        default:
            break;
    }

    return _choice == Choice::None;
}

void MainMenu::_build_text() {
    _text_sprites.clear();

    for(const Entry& e : _entries) {
        bn::string<16> label;

        switch(e.choice) {
            case Choice::Continue:
                label = "CONTINUE";
                break;
            case Choice::NewGame:
                label = "NEW GAME";
                break;
            case Choice::EReader:
                label = "E-READER";
                break;
            case Choice::Option:
                label = "OPTION";
                break;
            default:
                continue;
        }

        int x = tile_to_screen_x(menu_left_tile + 1);
        int y = tile_to_screen_y(e.top_tile + 1) + 8;
        _text_generator.generate(x, y, label, _text_sprites);
    }

    for(auto& s : _text_sprites) {
        s.set_blending_enabled(true);
    }
}

void MainMenu::_update_fade_in() {
    // TODO: Fade in
}

void MainMenu::_update_fade_out() {
    // TODO: Fade out
}

void MainMenu::_handle_input() {
    bool moved = false;

    if(_state == State::WaitInput) {
        if(bn::keypad::up_pressed()) {
            if(_selected_idx > 0) {
                --_selected_idx;
                moved = true;
            }
        } else if(bn::keypad::down_pressed()) {
            if(_selected_idx < _entries.size()) {
                ++_selected_idx;
                moved = true;
            }
        }

        if(moved) {
            _update_selection();
        }

        if(bn::keypad::a_pressed()) {
            _choice = _entries[_selected_idx].choice;
        }

        if(bn::keypad::l_held() && bn::keypad::b_held() && bn::keypad::up_held()) {
            _save_manager->erase_save();
        }
    }
}

MainMenu::Choice MainMenu::get_choice() {
    return _choice;
}
