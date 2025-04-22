#include "battle_cursor.h"
#include "battle_engine.h"
#include "cursor_controller.h"
#include "field.h"
#include "zone.h"

class BattleCursorController : public CursorController {
    private:
        BattleCursor& m_cursor;
        BattleEngine& m_battle_engine;
    public:
        BattleCursorController(BattleCursor& cursor, BattleEngine& battle_engine);
        void update() override;
    private:
        void snap_to_zone(ZoneId zone_id, Side side = Side::SIDE_PLAYER);
};