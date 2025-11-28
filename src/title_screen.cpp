#include "title_screen.h"
#include "bn_backdrop.h"
#include "bn_blending.h"
#include "bn_color.h"
#include "bn_display.h"
#include "bn_keypad.h"
#include "bn_random.h"
#include "bn_regular_bg_items_pokemon_logo.h"
#include "bn_sprite_items_card_sheet_1.h"
#include "bn_sprite_items_card_sheet_2.h"
#include "bn_sprite_items_card_sheet_3.h"
#include "bn_sprite_items_energy_sheet_1.h"
#include "bn_sprite_items_energy_sheet_2.h"
#include "bn_sprite_items_energy_sheet_3.h"
#include "bn_sprite_items_press_start_left.h"
#include "bn_sprite_items_press_start_right.h"
#include "bn_sprite_items_tcg_left.h"
#include "bn_sprite_items_tcg_right.h"

namespace {
    constexpr int screen_height = bn::display::height();
    bn::array<bn::color, screen_height> backdrop_gradient_colors;
    constexpr bn::color white_color(31, 31, 31);
    constexpr bn::color rainbow_keys[] = {
        bn::color(10, 25, 10),
        bn::color(31, 10, 2),
        bn::color(5, 15, 31),
        bn::color(31, 31, 5),
        bn::color(20, 5, 20),
        bn::color(20, 10, 2),
        bn::color(5, 5, 8),
        bn::color(25, 25, 28)
    };
    constexpr int rainbow_key_count = sizeof(rainbow_keys) / sizeof(rainbow_keys[0]);

    bn::color lerp_color(bn::color a, bn::color b, bn::fixed t) {
        bn::fixed one_minus_t = 1 - t;
        int ar = a.red();
        int ag = a.green();
        int ab = a.blue();
        int br = b.red();
        int bg = b.green();
        int bb = b.blue();
        int fr = (bn::fixed(ar) * one_minus_t + bn::fixed(br) * t).round_integer();
        int fg = (bn::fixed(ag) * one_minus_t + bn::fixed(bg) * t).round_integer();
        int fb = (bn::fixed(ab) * one_minus_t + bn::fixed(bb) * t).round_integer();
        fr = bn::max(0, bn::min(31, fr));
        fg = bn::max(0, bn::min(31, fg));
        fb = bn::max(0, bn::min(31, fb));

        return bn::color(fr, fg, fb);
    }

    void rebuild_rainbow_gradient(int phase) {
        constexpr int band_height = 32;
        constexpr int pulse_period = 120;
        const int total_cycle = pulse_period * rainbow_key_count;
        int cycle_pos = phase % total_cycle;
        int color_idx = cycle_pos / pulse_period;
        int color_phase = cycle_pos % pulse_period;
        bn::fixed t = bn::fixed(color_phase) / bn::fixed(pulse_period);
        bn::fixed pulse;

        if(t <= bn::fixed(0.5)) {
            pulse = t * 2;
        } else {
            pulse = (1 - t) * 2;
        }

        bn::color base = rainbow_keys[color_idx];

        for(int y = 0; y < screen_height; ++y) {
            bn::color final_color = white_color;

            if(y < band_height) {
                int band_pos = y;
                bn::fixed band_t = bn::fixed(band_pos) / bn::fixed(band_height - 1);
                bn::fixed strength = (1 - band_t) * pulse;
                final_color = lerp_color(white_color, base, strength);
            } else if(y >= screen_height - band_height) {
                int band_pos = (screen_height - 1) - y;
                bn::fixed band_t = bn::fixed(band_pos) / bn::fixed(band_height - 1);
                bn::fixed strength = (1 - band_t) * pulse;
                final_color = lerp_color(white_color, base, strength);
            }

            backdrop_gradient_colors[y] = final_color;
        }
    }

    bn::backdrop_color_hbe_ptr create_rainbow_gradient_hbe() {
        rebuild_rainbow_gradient(0);
        return bn::backdrop_color_hbe_ptr::create(backdrop_gradient_colors);
    }

    constexpr int cards_count = 4;
    constexpr int lane_left = -96;
    constexpr int lane_right = 96;
    constexpr int lane_spacing = (lane_right - lane_left) / (cards_count - 1);
    constexpr int lane_jitter = 8;
    bn::random random_generator;

    int lane_center_x(int lane) {
        return lane_left + lane_spacing * lane;
    }

    int lane_random_x(int lane) {
        int base = lane_center_x(lane);
        int jitter = random_generator.get_int(-lane_jitter, lane_jitter);
        return base + jitter;
    }
}

TitleScreen::TitleScreen() :  _state(State::FadeInLogo), _timer(0), _blink_timer(0), _blink_visible(true) {
    bn::backdrop::set_color(bn::color(0, 0, 0));
    bn::blending::set_black_fade_color();
    bn::blending::set_fade_alpha(1);
    _load_bg();

    _tcg_sprites.push_back(bn::sprite_items::tcg_left.create_sprite(-32, 23));
    _tcg_sprites.push_back(bn::sprite_items::tcg_right.create_sprite(32, 23));
    _press_start_sprites.push_back(bn::sprite_items::press_start_left.create_sprite(-32, 60));
    _press_start_sprites.push_back(bn::sprite_items::press_start_right.create_sprite(32, 60));

    for(auto& sprite : _tcg_sprites) {
        sprite.set_visible(false);
    }

    for(auto& sprite : _press_start_sprites) {
        sprite.set_visible(false);
    }
}

void TitleScreen::_load_bg() {
    _bg = bn::regular_bg_items::pokemon_logo.create_bg(0, 31);
    _bg->set_priority(2);
    _bg->set_blending_enabled(true);
    _timer = 0;
    _blink_timer = 0;
    _blink_visible = false;
}

bool TitleScreen::update() {
    _handle_input();

    switch(_state) {
        case State::FadeInLogo:
            _update_fade_in_logo();
            break;
        case State::FadeInTCG:
            _update_fade_in_tcg();
            break;
        case State::LogoAnim:
            _update_logo_anim();
            break;
        case State::WaitInput:
            _update_wait_input();
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

void TitleScreen::_handle_input() {
    if(_state == State::WaitInput) {
        if(bn::keypad::start_pressed() || bn::keypad::a_pressed()) {
            _state = State::FadeOut;
            _timer = 0;
        }
    } else if(_state == State::FadeInLogo || _state == State::FadeInTCG || _state == State::LogoAnim) {
        if(bn::keypad::any_pressed()) {
            _skip();
        }
    }
}

void TitleScreen::_update_fade_in_logo() {
    bn::fixed t = clamp_lerp(_timer, fade_duration);
    bn::blending::set_fade_alpha(1 - t);

    if(++_timer >= fade_duration) {
        _bg->set_blending_enabled(false);
        bn::blending::set_fade_alpha(1);
        _state = State::FadeInTCG;
        _timer = 0;

        for(auto& sprite : _tcg_sprites) {
            sprite.set_visible(true);
            sprite.set_blending_enabled(true);
        }
    }
}

void TitleScreen::_update_fade_in_tcg() {
    bn::fixed t = clamp_lerp(_timer, fade_duration);
    bn::blending::set_fade_alpha(1 - t);

    if(++_timer >= fade_duration) {
        bn::blending::set_fade_alpha(0);

        for(auto& sprite : _tcg_sprites) {
            sprite.set_blending_enabled(false);
        }

        _state = State::LogoAnim;
        _timer = 0;
    }
}

void TitleScreen::_update_logo_anim() {
    if(!_logo_move_action) {
        _logo_move_action = bn::regular_bg_move_to_action(*_bg, anim_duration, 0, 0);
        _tcg_left_action = bn::sprite_move_to_action(_tcg_sprites[0], anim_duration, -32, -8);
        _tcg_right_action = bn::sprite_move_to_action(_tcg_sprites[1], anim_duration, 32, -8);
    }

    bool done = true;

    if(_logo_move_action && !_logo_move_action->done()) {
        _logo_move_action->update();
        done = false;
    }

    if(_tcg_left_action && !_tcg_left_action->done()) {
        _tcg_left_action->update();
        done = false;
    }

    if(_tcg_right_action && !_tcg_right_action->done()) {
        _tcg_right_action->update();
        done = false;
    }

    if(done) {
        _logo_move_action.reset();
        _tcg_left_action.reset();
        _tcg_right_action.reset();
        bn::backdrop::set_color(bn::color(31, 31, 31));
        _state = State::WaitInput;
        return;
    }
}

void TitleScreen::_update_wait_input() {
    if(!_backdrop_color_hbe.has_value()) {
         _backdrop_color_hbe = create_rainbow_gradient_hbe(); 
    }

    if(_cards.size() < cards_count) {
        _init_cards();
    }

    constexpr int frames_per_step = 5;
    constexpr int phase_step = 1;
    _update_press_text_blink();
    _update_cards();

    if(++_gradient_timer >= frames_per_step) {
        _gradient_timer = 0;
        _gradient_phase += phase_step;
        rebuild_rainbow_gradient(_gradient_phase);
        _backdrop_color_hbe->reload_colors_ref();
    }
}

void TitleScreen::_update_press_text_blink() {
    if(++_blink_timer >= blink_interval) {
        _blink_timer = 0;
        _blink_visible = !_blink_visible;

        for(auto& sprite : _press_start_sprites) {
            sprite.set_visible(_blink_visible);
        }
    }
}

void TitleScreen::_update_fade_out() {
    bn::blending::set_white_fade_color();
    
    if(_timer == 0) {
        _bg->set_blending_enabled(true);
        
        for(auto& sprite : _tcg_sprites) {
            sprite.set_blending_enabled(true);
        }

        for(auto& sprite : _press_start_sprites) {
            sprite.set_blending_enabled(true);
        }
    }

    bn::fixed t = clamp_lerp(_timer, fade_duration);
    bn::blending::set_fade_alpha(t);

    if(++_timer >= fade_duration) {
        bn::blending::set_fade_alpha(1);
        _state = State::Done;
    }
}

void TitleScreen::_skip() {
    bn::blending::set_fade_alpha(0);
    _bg->set_y(0);
    _bg->set_blending_enabled(false);
    _tcg_sprites[0].set_position(-32, -8);
    _tcg_sprites[1].set_position(32, -8);

    for(auto& sprite : _tcg_sprites) {
        sprite.set_visible(true);
        sprite.set_blending_enabled(false);
    }

    bn::backdrop::set_color(bn::color(31, 31, 31));
    _logo_move_action.reset();
    _tcg_left_action.reset();
    _tcg_right_action.reset();
    _timer = 0;
    _state = State::WaitInput;

    for(auto& sprite : _press_start_sprites) {
        sprite.set_visible(true);
    }
}

inline bn::fixed TitleScreen::clamp_lerp(int time, int duration) {
    bn::fixed t = bn::fixed(time) / duration;
    return bn::clamp(t, bn::fixed(0), bn::fixed(1));
}

void TitleScreen::_init_cards() {
    _cards.clear();

    for(int i = 0; i < cards_count; ++i) {
        int lane = i;
        int x = lane_random_x(lane);
        bn::fixed y = bn::fixed(80 + random_generator.get_int(0, 40));
        bn::fixed speed = bn::fixed(0.3) + bn::fixed(random_generator.get_int(0, 5)) / 10;
        bn::sprite_ptr sprite = bn::sprite_items::card_sheet_1.create_sprite(x, y.round_integer());
        int sheet = random_generator.get_int(0, 5);

        if(sheet == 0) {
            int card = random_generator.get_int(0, 3);
            sprite = bn::sprite_items::card_sheet_1.create_sprite(x, y.round_integer(), card);
        }

        if(sheet == 1) {
            int card = random_generator.get_int(0, 3);
            sprite = bn::sprite_items::card_sheet_2.create_sprite(x, y.round_integer(), card);
        }

        if(sheet == 2) {
            int card = random_generator.get_int(0, 1);
            sprite = bn::sprite_items::card_sheet_3.create_sprite(x, y.round_integer(), card);
        }

        if(sheet == 3) {
            int card = random_generator.get_int(0, 3);
            sprite = bn::sprite_items::energy_sheet_1.create_sprite(x, y.round_integer(), card);
        }

        if(sheet == 4) {
            int card = random_generator.get_int(0, 3);
            sprite = bn::sprite_items::energy_sheet_2.create_sprite(x, y.round_integer(), card);
        }

        if(sheet == 5) {
            sprite = bn::sprite_items::energy_sheet_3.create_sprite(x, y.round_integer());
        }

        sprite.set_blending_enabled(true);
        sprite.set_bg_priority(3);
        sprite.set_z_order(1);
        _cards.push_back({ bn::move(sprite), y, speed, lane });
    }
}

void TitleScreen::_update_cards() {
    constexpr bn::fixed bottom_y = bn::fixed(88);
    constexpr bn::fixed top_y = bn::fixed(-88);

    for(auto& c : _cards) {
        c.y -= c.speed;

        if(c.y <= top_y) {
            int x = lane_random_x(c.lane);
            c.y = bottom_y + bn::fixed(random_generator.get_int(0, 40));
            c.speed = bn::fixed(0.3) + bn::fixed(random_generator.get_int(0, 5)) / 10;
            int sheet = random_generator.get_int(0, 5);

            if(sheet == 0) {
                int card = random_generator.get_int(0, 3);
                c.sprite = bn::sprite_items::card_sheet_1.create_sprite(x, c.y.round_integer(), card);
            }

            if(sheet == 1) {
                int card = random_generator.get_int(0, 3);
                c.sprite = bn::sprite_items::card_sheet_2.create_sprite(x, c.y.round_integer(), card);
            }

            if(sheet == 2) {
                int card = random_generator.get_int(0, 1);
                c.sprite = bn::sprite_items::card_sheet_3.create_sprite(x, c.y.round_integer(), card);
            }

            if(sheet == 3) {
                int card = random_generator.get_int(0, 3);
                c.sprite = bn::sprite_items::energy_sheet_1.create_sprite(x, c.y.round_integer(), card);
            }

            if(sheet == 4) {
                int card = random_generator.get_int(0, 3);
                c.sprite = bn::sprite_items::energy_sheet_2.create_sprite(x, c.y.round_integer(), card);
            }

            if(sheet == 5) {
                c.sprite = bn::sprite_items::energy_sheet_3.create_sprite(x, c.y.round_integer());
            }
            
            c.sprite.set_blending_enabled(true);
            c.sprite.set_bg_priority(3);
            c.sprite.set_z_order(1);
            c.sprite.set_visible(true);
        } else {
            c.sprite.set_y(c.y.round_integer());
        }
    }
}