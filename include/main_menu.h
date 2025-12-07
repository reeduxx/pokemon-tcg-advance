#pragma once

#include "bn_optional.h"
#include "bn_rect_window.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sound_handle.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_time.h"
#include "bn_vector.h"
#include "bg_builder.h"
#include "save_manager.h"

class MainMenu {
    public:
        enum class Choice {
            None,
            BackToTitle,
            Continue,
            NewGame,
            EReader,
            Option
        };

        explicit MainMenu();
        bool update();
        Choice get_choice();
    private:
        enum class State {
            FadeIn,
            CheckRTC,
            ShowRTCWarning,
            WaitInput,
            FadeOut,
            Done
        };

        enum class RTCStatus {
            Unknown,
            Ok,
            NotPresent,
            Stopped
        };

        struct Entry {
            Choice choice;
            int top_tile;
            int height_tiles;
        };

        bn::optional<bn::regular_bg_ptr> _options_bg;
        bn::optional<bn::regular_bg_ptr> _bg;
        bn::optional<bn::rect_window> _selection_window;
        BgBuilder _bg_builder;
        bn::sprite_text_generator _text_generator;
        bn::optional<SaveManager> _save_manager;
        bn::optional<bn::sound_handle> _select_sfx;
        bn::optional<bn::time> _rtc_initial_time;
        static constexpr int max_entries = 4;
        bn::vector<Entry, max_entries> _entries;
        bn::vector<bn::sprite_ptr, 32> _text_sprites;
        bn::string<104> _rtc_message_text = "The internal battery has run dry.";
        int _timer;
        State _state = State::FadeIn;
        Choice _choice = Choice::None;
        int _selected_idx = 0;
        RTCStatus _rtc_status = RTCStatus::Unknown;
        bool _rtc_check_started = false;
        int _rtc_check_frames = 0;
        void _build_entries(bool has_save, bool ereader_enabled);
        void _create_bg();
        void _update_selection();
        void _build_text();
        void _update_fade_in();
        void _update_fade_out();
        void _handle_input();
        void _update_check_rtc();
        void _update_rtc_warning();
        void _build_rtc_message_box();
        void _start_main_menu();
};