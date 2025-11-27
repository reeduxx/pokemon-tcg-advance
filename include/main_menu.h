#pragma once

#include "bn_optional.h"
#include "bn_rect_window.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_vector.h"
#include "menu_builder.h"
#include "save_manager.h"

class MainMenu {
    public:
        enum class Choice {
            None,
            Continue,
            NewGame,
            EReader,
            Option
        };

        MainMenu();
        Choice update();
    private:
        enum class State {
            FadeIn,
            WaitInput,
            FadeOut,
            Done
        };

        struct Entry {
            Choice choice;
            int top_tile;
            int height_tiles;
        };

        static constexpr int max_entries = 4;
        MenuBuilder _menu_builder;
        bn::optional<bn::regular_bg_ptr> _options_bg;
        bn::optional<bn::regular_bg_ptr> _bg;
        bn::vector<Entry, max_entries> _entries;
        bn::optional<bn::rect_window> _selection_window;
        bn::sprite_text_generator _text_generator;
        bn::vector<bn::sprite_ptr, 32> _text_sprites;
        bn::optional<SaveManager> _save_manager;
        State _state;
        int _selected_idx = 0;
        void _build_entries(bool has_save, bool ereader_enabled);
        void _create_bg();
        void _update_selection();
        void _build_text();
        void _update_fade_in();
        void _update_fade_out();
        MainMenu::Choice _handle_input();
};