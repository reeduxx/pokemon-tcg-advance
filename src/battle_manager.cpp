#include "bn_regular_bg_items_card_name_bar.h"
#include "common_fixed_8x16_sprite_font.h"
#include "battle_manager.h"
#include "card_names.h"
#include "cards.h"

BattleManager::BattleManager() : 
    m_battle_cursor(), m_player_hand(false), m_opponent_hand(true), m_field(), m_battle_engine(m_battle_cursor, m_player_hand, 
    m_opponent_hand, m_field), m_battle_cursor_controller(m_battle_cursor, m_battle_engine), 
    m_text_generator(common::fixed_8x16_sprite_font), m_card_name_bar(bn::regular_bg_items::card_name_bar, m_text_generator) {
    m_battle_cursor.set_hand_idx(0);
}

void BattleManager::update() {
    if(m_battle_engine.current_state() == BattleState::SETUP_HANDS) {
        draw_hands();
    }

    m_battle_engine.update();
    update_input();
    update_visuals();
}

void BattleManager::update_input() {
    if(m_mode == InputMode::BATTLE) m_battle_cursor_controller.update();
    // TODO: Implement menus and menu cursor/cursor controller
    //if(m_mode == InputMode::MENU) m_menu_cursor_controller.update();
}

void BattleManager::update_visuals() {
    m_field.update();
    m_player_hand.update();
    m_opponent_hand.update();

    if(m_battle_cursor.mode() == CursorMode::HAND && m_battle_engine.is_player_turn()) {
        int i = m_battle_cursor.hand_idx();

        if(i >= 0 && i < m_player_hand.card_count()) {
            const BattleCard& card = m_player_hand.get_card(i);
            const Card* data = get_card_by_id(card.card_id);

            if(data) m_card_name_bar.set_text(get_card_name(data->header.name_id));
        } else {
            m_card_name_bar.clear();
        }
    } else if(m_battle_cursor.mode() == CursorMode::FIELD && m_battle_engine.is_player_turn()) {
        ZoneId zone_id = m_battle_cursor.zone();
        const Zone& zone = m_field.get_zone(zone_id);

        if(zone.occupied) {
            const BattleCard& card = zone.card;
            const Card* data = get_card_by_id(card.card_id);

            if(data) m_card_name_bar.set_text(get_card_name(data->header.name_id));
        } else {
            m_card_name_bar.clear();
        }
    } else {
        m_card_name_bar.clear();
    }
}

void BattleManager::draw_hands() {
    for(int i = 0; i < 7; ++i) {
        if(m_battle_engine.can_draw(TurnPlayer::PLAYER)) {
            m_player_hand.add_card(m_battle_engine.draw_card(TurnPlayer::PLAYER));
        }

        if(m_battle_engine.can_draw(TurnPlayer::OPPONENT)) {
            m_opponent_hand.add_card(m_battle_engine.draw_card(TurnPlayer::OPPONENT));
        }
    }

    m_opponent_hand.set_visible(false);
}

void BattleManager::try_draw_card(TurnPlayer turn_player) {
    switch(turn_player) {
        case TurnPlayer::PLAYER:
            if(m_battle_engine.can_draw(TurnPlayer::PLAYER)) {
                m_player_hand.add_card(m_battle_engine.draw_card(TurnPlayer::PLAYER));
            }
            break;
        case TurnPlayer::OPPONENT:
            if(m_battle_engine.can_draw(TurnPlayer::OPPONENT)) {
                m_opponent_hand.add_card(m_battle_engine.draw_card(TurnPlayer::OPPONENT));
            }
            break;
        default:
            break;
    }
}