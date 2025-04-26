#include "bn_vector.h"
#include "battle_cursor.h"
#include "battle_engine.h"
#include "cursor_controller.h"
#include "field.h"
#include "zone.h"

class BattleCursorController : public CursorController {
    private:
        BattleCursor& m_cursor;
        BattleEngine& m_battle_engine;
        bn::vector<ZoneId, 6> m_target_zones;
        int m_target_idx = 0;
    public:
        BattleCursorController(BattleCursor& cursor, BattleEngine& battle_engine);
        void update() override;
        void begin_target_selection(const bn::vector<ZoneId, 6>& target_zones);
        ZoneId target_zone() const;
        void cancel_target_selection();
    private:
        void snap_to_zone(ZoneId zone_id, Side side = Side::SIDE_PLAYER);
};