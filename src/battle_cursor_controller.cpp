#include "bn_keypad.h"
#include "battle_cursor_controller.h"

BattleCursorController::BattleCursorController(BattleCursor& cursor, BattleEngine& battle_engine) : m_cursor(cursor), m_battle_engine(battle_engine) {
    m_cursor.set_hand_idx(0);
    m_cursor.set_pos(m_battle_engine.player_hand().get_card_pos(0));
}

void BattleCursorController::update() {
    ZoneId zone_id = m_cursor.zone();

    if(m_cursor.mode() == CursorMode::HAND && m_cursor.pos() != m_battle_engine.player_hand().get_card_pos(m_cursor.hand_idx())) {
        m_cursor.set_pos(m_battle_engine.player_hand().get_card_pos(m_cursor.hand_idx()));
    }

    // Left
    if(bn::keypad::left_pressed()) {
        if(m_cursor.mode() == CursorMode::HAND) {
            int i = 0;

            if(m_cursor.hand_idx() > 0) {
                i = m_cursor.hand_idx() - 1;
            } else {
                i = m_battle_engine.player_hand().card_count() - 1;
            }

            m_cursor.set_hand_idx(i);
            m_cursor.set_pos(m_battle_engine.player_hand().get_card_pos(i));
        } else if(m_cursor.mode() == CursorMode::FIELD) {
            if(zone_id == ZoneId::PLAYER_BENCH_1) {
                snap_to_zone(ZoneId::PLAYER_PRIZES);
            } else if(zone_id > ZoneId::PLAYER_BENCH_1 && zone_id <= ZoneId::PLAYER_BENCH_5) {
                snap_to_zone(static_cast<ZoneId>(static_cast<int>(zone_id) - 1));
            } else if(zone_id == ZoneId::PLAYER_DISCARD) {
                snap_to_zone(ZoneId::PLAYER_BENCH_5);
            } else if(zone_id == ZoneId::PLAYER_ACTIVE || zone_id == ZoneId::OPPONENT_ACTIVE) {
                snap_to_zone(ZoneId::STADIUM, m_battle_engine.field().side());
            } else if(zone_id >= ZoneId::OPPONENT_BENCH_1 && zone_id <= ZoneId::OPPONENT_BENCH_5) {
                snap_to_zone(zone_id == ZoneId::OPPONENT_BENCH_1 ? ZoneId::OPPONENT_BENCH_5 : static_cast<ZoneId>(static_cast<int>(zone_id) - 1));
            }
        } else if(m_cursor.mode() == CursorMode::TARGET) {
            m_target_idx = (m_target_idx - 1 + m_target_zones.size()) % m_target_zones.size();
            snap_to_zone(m_target_zones[m_target_idx]);
        }
    }
    // Right
    if(bn::keypad::right_pressed()) {
        if(m_cursor.mode() == CursorMode::HAND) {
            int i = 0;
            
            if(m_cursor.hand_idx() < m_battle_engine.player_hand().card_count() - 1) {
                i = m_cursor.hand_idx() + 1;
            } else {
                i = 0;
            }

            m_cursor.set_hand_idx(i);
            m_cursor.set_pos(m_battle_engine.player_hand().get_card_pos(i));
        } else if(m_cursor.mode() == CursorMode::FIELD) {
            if(zone_id == ZoneId::PLAYER_PRIZES) {
                snap_to_zone(ZoneId::PLAYER_BENCH_1);
            } else if(zone_id >= ZoneId::PLAYER_BENCH_1 && zone_id < ZoneId::PLAYER_BENCH_5) {
                snap_to_zone(static_cast<ZoneId>(static_cast<int>(zone_id) + 1));
            } else if(zone_id == ZoneId::PLAYER_BENCH_5) {
                snap_to_zone(ZoneId::PLAYER_DISCARD);
            } else if(zone_id == ZoneId::STADIUM) {
                snap_to_zone(m_battle_engine.field().side() == Side::SIDE_PLAYER ? ZoneId::PLAYER_ACTIVE : ZoneId::OPPONENT_ACTIVE);
            } else if(zone_id >= ZoneId::OPPONENT_BENCH_1 && zone_id <= ZoneId::OPPONENT_BENCH_5) {
                snap_to_zone(zone_id == ZoneId::OPPONENT_BENCH_5 ? ZoneId::OPPONENT_BENCH_1 : static_cast<ZoneId>(static_cast<int>(zone_id) + 1));
            }
        } else if(m_cursor.mode() == CursorMode::TARGET) {
            m_target_idx = (m_target_idx + 1) % m_target_zones.size();
            snap_to_zone(m_target_zones[m_target_idx]);
        }
    }
    // Up
    if(bn::keypad::up_pressed() && m_battle_engine.current_state() >= BattleState::BATTLE_START) {
        if(m_cursor.mode() == CursorMode::HAND) {
            m_cursor.set_mode(CursorMode::FIELD);
            snap_to_zone(ZoneId::PLAYER_BENCH_1);
        } else if(m_cursor.mode() == CursorMode::FIELD) {
            if(zone_id >= ZoneId::PLAYER_BENCH_1 && zone_id <= ZoneId::PLAYER_BENCH_5) {
                snap_to_zone(ZoneId::PLAYER_ACTIVE);
            } else if(zone_id == ZoneId::PLAYER_DISCARD) {
                snap_to_zone(ZoneId::PLAYER_DECK);
            } else if(zone_id == ZoneId::PLAYER_ACTIVE) {
                m_battle_engine.field().scroll_to_opponent();
                m_battle_engine.opponent_hand().set_visible(true);
                m_battle_engine.player_hand().set_visible(false);
                snap_to_zone(ZoneId::OPPONENT_ACTIVE);
            } else if(zone_id == ZoneId::OPPONENT_ACTIVE) {
                snap_to_zone(ZoneId::OPPONENT_BENCH_1);
            }
        }
    }
    // Down
    if(bn::keypad::down_pressed() && m_battle_engine.current_state() >= BattleState::BATTLE_START) {
        if(m_cursor.mode() == CursorMode::FIELD) {
            if(zone_id >= ZoneId::OPPONENT_BENCH_1 && zone_id <= ZoneId::OPPONENT_BENCH_5) {
                snap_to_zone(ZoneId::OPPONENT_ACTIVE);
            } else if(zone_id == ZoneId::OPPONENT_ACTIVE) {
                m_battle_engine.field().scroll_to_player();
                m_battle_engine.player_hand().set_visible(true);
                m_battle_engine.opponent_hand().set_visible(false);
                snap_to_zone(ZoneId::PLAYER_ACTIVE);
            } else if(zone_id == ZoneId::PLAYER_ACTIVE) {
                snap_to_zone(ZoneId::PLAYER_BENCH_1);
            } else if(zone_id >= ZoneId::PLAYER_BENCH_1 && zone_id <= ZoneId::PLAYER_BENCH_5) {
                if(m_battle_engine.player_hand().card_count() > 0) {
                    m_cursor.set_mode(CursorMode::HAND);
                    m_cursor.set_hand_idx(0);
                    m_cursor.set_pos(m_battle_engine.player_hand().get_card_pos(0));
                }
            } else if(zone_id == ZoneId::PLAYER_DECK) {
                snap_to_zone(ZoneId::PLAYER_DISCARD);
            }
        }
    }
}

void BattleCursorController::snap_to_zone(ZoneId zone_id, Side side) {
    m_cursor.set_zone(zone_id);

    if(side == Side::SIDE_PLAYER) {
        m_cursor.set_pos(m_battle_engine.field().get_zone(zone_id).m_pos);
    } else {
        m_cursor.set_pos(m_battle_engine.field().get_zone(zone_id).m_opponent_pos);
    }
}

void BattleCursorController::begin_target_selection(const bn::vector<ZoneId, 6>& target_zones) {
    m_target_zones = target_zones;
    m_target_idx = 0;
    m_cursor.set_mode(CursorMode::TARGET);
    snap_to_zone(m_target_zones[m_target_idx]);
}

ZoneId BattleCursorController::target_zone() const {
    return m_target_zones[m_target_idx];
}

void BattleCursorController::cancel_target_selection() {
    m_target_zones.clear();
    m_cursor.set_mode(CursorMode::HAND);
}