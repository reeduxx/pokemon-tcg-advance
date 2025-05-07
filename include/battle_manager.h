#ifndef GUARD_BATTLE_MANAGER_H
#define GUARD_BATTLE_MANAGER_H

#include "bn_optional.h"
#include "bn_sprite_text_generator.h"
#include "battle_engine.h"
#include "card_name_bar.h"
#include "battle_card.h"
#include "battle_cursor.h"
#include "battle_cursor_controller.h"
#include "field.h"
#include "hand.h"
#include "menu.h"
#include "menu_cursor.h"
#include "menu_cursor_controller.h"

enum class InputMode {
    BATTLE,
    ENERGY,
    EVOLUTION,
    MENU,
    RETREAT
};

class BattleManager {
    private:
        BattleCursor m_battle_cursor;
        MenuCursor m_menu_cursor;
        Hand m_player_hand, m_opponent_hand;
        Field m_field;
        BattleEngine m_battle_engine;
        BattleCursorController m_battle_cursor_controller;
        bn::sprite_text_generator m_text_generator;
        CardNameBar m_card_name_bar;
        Menu m_menu;
        MenuCursorController m_menu_cursor_controller;
        InputMode m_mode = InputMode::BATTLE;
        BattleCard* m_selected_card = nullptr;
    public:
        BattleManager();
        void update();
        void draw_hands();
        void try_draw_card(TurnPlayer turn_player);
    private:
        void update_input();
        void update_visuals();
        void show_card_menu(BattleCard& card);
        void execute_menu_action(int i);
};

#endif // GUARD_BATTLE_MANAGER_H