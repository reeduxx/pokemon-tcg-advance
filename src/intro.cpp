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

Intro::Intro() : _current_idx(0), _state(State::FadeIn), _timer(0), _blink_timer(0), _blink_visible(true) {
    bn::blending::set_black_fade_color();
    bn::blending::set_fade_alpha(1);
    _splashes.push_back({ bn::regular_bg_items::health_and_safety_splash, 30, -1, 30, true });
    _splashes.push_back({ bn::regular_bg_items::judgmental_frog_studios_splash, 30, 60, 30, false });
    _splashes.push_back({ bn::regular_bg_items::butano_splash, 30, 60, 30, false });

    _press_text_sprites.push_back(bn::sprite_items::health_and_safety_text_0.create_sprite(-68, 64));
    _press_text_sprites.push_back(bn::sprite_items::health_and_safety_text_1.create_sprite(-4, 64));
    _press_text_sprites.push_back(bn::sprite_items::health_and_safety_text_2.create_sprite(60, 64));
    _press_text_sprites.push_back(bn::sprite_items::health_and_safety_text_3.create_sprite(96, 64));

    for(bn::sprite_ptr& sprite : _press_text_sprites) {
        sprite.set_visible(false);
    }

    _load_current_splash();
}

bool Intro::update() {
    _skip_requested();

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

    return false;
}

void Intro::_load_current_splash() {
    if(_bg) {
        _bg.reset();
    }

    const splash& s = _splashes[_current_idx];
    _bg = s.bg.create_bg(0, 0);
    _bg->set_blending_enabled(true);
    _timer = 0;
    bn::blending::set_fade_alpha(1);
    
    if(!s.show_press && !_press_text_sprites.empty()) {
        _press_text_sprites.clear();
    }

    _blink_timer = 0;
    _blink_visible = true;
}

void Intro::_skip_requested() {
    if(_state == State:: FadeIn || _state == State::Hold) {
        if(bn::keypad::a_pressed()) {
            _state = State::FadeOut;
            _timer = 0;
            return;
        } else if(bn::keypad::start_pressed()) {
            _state = State::Done;
            return;
        }
    }
}

void Intro::_update_fade_in() {
    const splash& s = _splashes[_current_idx];

    if(s.fade_in <= 0) {
        bn::blending::set_fade_alpha(0);
        _state = State::Hold;
        _timer = 0;
        return;
    }

    bn::fixed t = bn::fixed(_timer) / s.fade_in;
    t = bn::max(bn::fixed(0), bn::min(t, bn::fixed(1)));
    bn::blending::set_fade_alpha(1 - t);

    if(_timer >= s.fade_in) {
        bn::blending::set_fade_alpha(0);
        _state = State::Hold;
        _timer = 0;
    } else {
        ++_timer;
    }
}

void Intro::_update_hold() {
    const splash& s = _splashes[_current_idx];

    if(s.show_press) {
        _update_press_text_blink();
    }

    if(s.hold >= 0 && _timer >= s.hold) {
        _state = State::FadeOut;
        _timer = 0;
    }

    ++_timer;
}

void Intro::_update_press_text_blink() {
    constexpr int blink_interval = 20;

    if(++_blink_timer >= blink_interval) {
        _blink_timer = 0;
        _blink_visible = !_blink_visible;

        for(bn::sprite_ptr& sprite : _press_text_sprites) {
            sprite.set_visible(_blink_visible);
        }
    }
}

void Intro::_update_fade_out() {
    const splash& s = _splashes[_current_idx];

    if(s.fade_out <= 0) {
        bn::blending::set_fade_alpha(1);
    } else {
        bn::fixed t = bn::fixed(_timer) / s.fade_out;
        t = bn::max(bn::fixed(0), bn::min(t, bn::fixed(1)));
        bn::blending::set_fade_alpha(t);
    }

    if(_timer >= s.fade_out) {
        bn::blending::set_fade_alpha(1);

        if(_current_idx + 1 < _splashes.size()) {
            ++_current_idx;
            _state = State::FadeIn;
            _load_current_splash();
        } else {
            _state = State::Done;
        }
    } else {
        ++_timer;
    }
}