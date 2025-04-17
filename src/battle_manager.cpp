#include "bn_regular_bg_items_card_name_bar.h"
#include "common_fixed_8x16_sprite_font.h"
#include "battle_manager.h"

BattleManager::BattleManager() : 
    m_battle_cursor(), m_player_hand(false), m_opponent_hand(true), m_field(), m_battle_engine(m_battle_cursor, m_player_hand, 
    m_opponent_hand, m_field), m_battle_cursor_controller(m_battle_cursor, m_battle_engine), 
    m_text_generator(common::fixed_8x16_sprite_font), m_card_name_bar(bn::regular_bg_items::card_name_bar, m_text_generator) {
    m_battle_cursor.set_hand_idx(0);
}

void BattleManager::update() {
    m_battle_engine.update();
    update_input();
    update_visuals();
}

void BattleManager::update_input() {
    if(m_mode == InputMode::BATTLE) m_battle_cursor_controller.update();
    //if(m_mode == InputMode::MENU) m_menu_cursor_controller.update();
}

void BattleManager::update_visuals() {
    m_field.update();
    m_player_hand.update();
    m_opponent_hand.update();
}