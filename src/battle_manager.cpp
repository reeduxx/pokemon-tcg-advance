#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_sprite_font.h"
#include "bn_regular_bg_items_card_name_bar.h"
#include "bn_regular_bg_tiles_items_border_test.h"
#include "battle_manager.h"
#include "card_names.h"
#include "cards.h"
#include "font.h"

BattleManager::BattleManager() : 
    m_battle_cursor(), m_menu_cursor(), m_player_hand(false), m_opponent_hand(true), m_field(), 
    m_battle_engine(m_battle_cursor, m_player_hand, m_opponent_hand, m_field), 
    m_battle_cursor_controller(m_battle_cursor, m_battle_engine),
    m_text_generator(font::font), m_card_name_bar(bn::regular_bg_items::card_name_bar, m_text_generator), 
    m_menu(27, 13, 4, 4, bn::regular_bg_tiles_items::border_test, bn::regular_bg_tiles_items::border_test_palette, m_text_generator), 
    m_menu_cursor_controller(m_menu_cursor, m_menu) {
    m_battle_cursor.set_hand_idx(0);
    m_menu_cursor.set_visible(false);
    m_menu.hide();
}

void BattleManager::update() {
    m_battle_engine.update();
    update_input();
    update_visuals();
}

void BattleManager::update_input() {
    if(m_mode == InputMode::BATTLE) {
        m_battle_cursor_controller.update();

        if(m_battle_engine.current_state() > BattleState::BATTLE_START) {
            if(bn::keypad::a_pressed()) {
                if(m_battle_cursor.mode() == CursorMode::HAND) {
                    int i = m_battle_cursor.hand_idx();
                    const BattleCard& card = m_player_hand.get_card(i);
                    show_card_menu(card);
                    return;
                } else if(m_battle_cursor.mode() == CursorMode::FIELD) {
                    ZoneId zone_id = m_battle_cursor.zone();
                    const Zone& zone_data = m_field.get_zone(zone_id);

                    if(zone_data.occupied) {
                        const BattleCard& card = zone_data.card;
                        show_card_menu(card);
                        return;
                    }
                }
            }
        }
    }
    
    if(m_mode == InputMode::MENU) {
        m_menu_cursor_controller.update();

        if(bn::keypad::a_pressed()) {
            int i = m_menu_cursor.idx();
            execute_menu_action(i);
            m_menu.hide();
            m_menu_cursor.set_visible(false);
            m_mode = InputMode::BATTLE;
        }

        if(bn::keypad::b_pressed()) {
            m_menu.hide();
            m_menu_cursor.set_visible(false);
            m_mode = InputMode::BATTLE;
        }
    }
}

void BattleManager::update_visuals() {
    if(m_battle_engine.current_state() == BattleState::COIN_FLIP || m_battle_engine.current_state() == BattleState::OPPONENT_TURN) {
        m_battle_cursor.set_visible(false);
    } else {
        m_battle_cursor.set_visible(true);
    }
    
    m_battle_cursor.update();
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

void BattleManager::show_card_menu(const BattleCard& card) {
    bn::array<bn::string<24>, 4> options;
    int count = 0;
    const Card* data = get_card_by_id(card.card_id);

    if(!data) {
        return;
    }

    if(data->header.type == CardType::CARD_POKEMON) {
        if(m_battle_cursor.mode() == CursorMode::HAND) {
            if(data->pokemon.stage == 0 || data->pokemon.stage == 1) {
                for(ZoneId zone_id = ZoneId::PLAYER_BENCH_1; zone_id <= ZoneId::PLAYER_BENCH_5; zone_id = static_cast<ZoneId>(static_cast<int>(zone_id) + 1)) {
                    Zone zone = m_field.get_zone(zone_id);
    
                    if(!zone.occupied) {
                        options[count++] = "PLAY";
                        break;
                    }
                }
            } else if(data->pokemon.stage > 0) {
                for(ZoneId zone_id = ZoneId::PLAYER_BENCH_1; zone_id <= ZoneId::PLAYER_ACTIVE; zone_id = static_cast<ZoneId>(static_cast<int>(zone_id) + 1)) {
                    Zone zone = m_field.get_zone(zone_id);
                    
                    if(zone.occupied) {
                        BattleCard& from_card = zone.card;
                        if(from_card.can_evolve && m_battle_engine.can_evolve(from_card, card)) {
                            options[count++] = "EVOLVE";
                            break;
                        }
                    }
                }
            }
        } else if(m_battle_cursor.mode() == CursorMode::FIELD) {
            options[count++] = "RETREAT";
        }
    } else if(data->header.type == CardType::CARD_TRAINER) {
        options[count++] = "PLAY";
    } else if(data->header.type == CardType::CARD_ENERGY) {
        options[count++] = "ATTACH";
    }

    options[count++] = "VIEW";
    options[count++] = "CANCEL";
    m_menu.set_options(bn::span(options.begin(), count));
    m_menu.show();
    m_menu.draw_text();
    m_menu_cursor.set_visible(true);
    m_menu_cursor.set_idx(0);
    m_menu_cursor.set_pos(m_menu.option_pos(0));
    m_mode = InputMode::MENU;
    m_selected_card = card;
}

void BattleManager::execute_menu_action(int i) {
    const Card* data = get_card_by_id(m_selected_card.card_id);

    if(!data) {
        return;
    }

    const bn::string<24>& action = m_menu.option(i);

    if(action == "ATTACH") {
        return;
    } else if(action == "CANCEL") {
        return;
    } else if(action == "EVOLVE") {
        for(ZoneId zone_id = ZoneId::PLAYER_BENCH_1; zone_id <= ZoneId::PLAYER_ACTIVE; zone_id = static_cast<ZoneId>(static_cast<int>(zone_id) + 1)) {
            Zone& zone = m_field.get_zone(zone_id);

            if(zone.occupied && m_battle_engine.can_evolve(zone.card, m_selected_card)) {
                // TODO: Finish implementing evolution.
                return;
            }
        }
    } else if(action == "PLAY") {
        return;
    } else if(action == "VIEW") {
        return;
    }
}