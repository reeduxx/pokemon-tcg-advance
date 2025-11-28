#include "intro.h"

#include "bn_blending.h"
#include "bn_keypad.h"
#include "bn_regular_bg_items_butano_splash.h"
#include "bn_regular_bg_items_health_and_safety_splash.h"
#include "bn_regular_bg_items_judgmental_frog_studios_splash.h"
#include "bn_sprite_items_health_and_safety_text_0.h"
#include "bn_sprite_items_health_and_safety_text_1.h"
#include "bn_sprite_items_health_and_safety_text_2.h"
#include "bn_sprite_items_health_and_safety_text_3.h"

namespace {
    constexpr int press_text_blink_period = 30;
}

Intro::Intro() {
    bn::blending::set_black_fade_color();
    bn::blending::set_fade_alpha(1);
    _splashes.push_back({ bn::regular_bg_items::health_and_safety_splash, 30, -1, 30, true });
    _splashes.push_back({ bn::regular_bg_items::judgmental_frog_studios_splash, 30, 60, 30, false });
    _splashes.push_back({ bn::regular_bg_items::butano_splash, 30, 60, 30, false });
    _load_current_splash();
}

bool Intro::update() {
    switch(_state) {
        case State::FadeIn:
            _update_fade_in();
            break;
        case State::Hold:
            _update_hold();
            break;
        case State::FadeOut:
            _update_fade_out();
            break; 
        case State::Done:
            return true;
        default:
            break;
    }

    return _state == State::Done;
}

void Intro::_load_current_splash() {
    const Splash& splash = _splashes[_current_idx];
    
    if(_bg) {
        _bg.reset();
    }

    _bg = splash.bg.create_bg(0, 0);
    _bg->set_blending_enabled(true);
    _timer = 0;
    _press_text_sprites.clear();
    _blink_timer = 0;
    _blink_visible = true;

    if(splash.show_press_text) {
        _load_press_text_sprites();
    }

    bn::blending::set_fade_alpha(1);
}

void Intro::_load_press_text_sprites() {
    constexpr int x_positions[4] = { -68, -4, 60, 96 };
    _press_text_sprites.push_back(bn::sprite_items::health_and_safety_text_0.create_sprite(x_positions[0], 64));
    _press_text_sprites.push_back(bn::sprite_items::health_and_safety_text_1.create_sprite(x_positions[1], 64));
    _press_text_sprites.push_back(bn::sprite_items::health_and_safety_text_2.create_sprite(x_positions[2], 64));
    _press_text_sprites.push_back(bn::sprite_items::health_and_safety_text_3.create_sprite(x_positions[3], 64));

    for(bn::sprite_ptr& sprite : _press_text_sprites) {
        sprite.set_visible(false);
    }
}

void Intro::_update_fade_in() {
    const Splash& splash = _splashes[_current_idx];
    
    if(_current_idx != 0) {
        if(bn::keypad::a_pressed()) {
            _state = State::FadeOut;
            _timer = 0;
            return;
        } else if(bn::keypad::start_pressed()) {
            _state = State::Done;
            _timer = 0;
            return;
        }
    }

    if(_timer >= splash.fade_in_frames) {
        bn::blending::set_fade_alpha(0);
        _state = State::Hold;
        _timer = 0;
    } else {
        bn::fixed t = bn::fixed(_timer) / splash.fade_in_frames;
        bn::fixed a = bn::fixed(1) - t;
        bn::blending::set_fade_alpha(a);
        ++_timer;
    }
}

void Intro::_update_hold() {
    const Splash& splash = _splashes[_current_idx];

    if(splash.show_press_text) {
        _update_press_text_blink();
    }

    if(_current_idx == 0) {
        if(bn::keypad::any_pressed()) {
            _state = State::FadeOut;
            _timer = 0;
        }
    } else {
        if(bn::keypad::a_pressed()) {
            _state = State::FadeOut;
            _timer = 0;
        } else if(bn::keypad::start_pressed()) {
            _state = State::Done;
            _timer = 0;
        }
    }

    if(splash.hold_frames < 0) {
        return;
    }
    
    if(_timer >= splash.hold_frames) {
        _state = State::FadeOut;
        _timer = 0;
    } else {
        ++_timer;
    }
}

void Intro::_update_fade_out() {
    const Splash& splash = _splashes[_current_idx];

    if(_timer >= splash.fade_out_frames) {
        bn::blending::set_fade_alpha(1);

        if(_current_idx + 1 < _splashes.size()) {
            ++_current_idx;
            _state = State::FadeIn;
            _load_current_splash();
        } else {
            _state = State::Done;
        }
    } else {
        bn::fixed t = bn::fixed(_timer) / splash.fade_out_frames;
        bn::fixed a = t;
        bn::blending::set_fade_alpha(a);
        ++_timer;
    }
}

void Intro::_update_press_text_blink() {
    ++_blink_timer;

    if(_blink_timer >= press_text_blink_period) {
        _blink_timer = 0;
        _blink_visible = !_blink_visible;

        for(bn::sprite_ptr& sprite : _press_text_sprites) {
            sprite.set_visible(_blink_visible);
        }
    }
}
