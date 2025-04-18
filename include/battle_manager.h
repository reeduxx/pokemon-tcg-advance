#ifndef GUARD_BATTLE_MANAGER_H
#define GUARD_BATTLE_MANAGER_H

#include "bn_optional.h"
#include "bn_sprite_text_generator.h"
#include "battle_engine.h"
#include "card_name_bar.h"
#include "cursor.h"
#include "cursor_controller.h"
#include "field.h"
#include "hand.h"

enum class InputMode {
    BATTLE,
    MENU
};

class BattleManager {
    private:
        Cursor m_battle_cursor;
        Hand m_player_hand, m_opponent_hand;
        Field m_field;
        BattleEngine m_battle_engine;
        CursorController m_battle_cursor_controller;
        bn::sprite_text_generator m_text_generator;
        CardNameBar m_card_name_bar;
        InputMode m_mode = InputMode::BATTLE;
    public:
        BattleManager();
        void update();
        void draw_hands();
        void try_draw_card(TurnPlayer turn_player);
    private:
        void update_input();
        void update_visuals();
};

#endif // GUARD_BATTLE_MANAGER_H