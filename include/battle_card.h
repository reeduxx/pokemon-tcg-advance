#ifndef GUARD_BATTLE_CARD_H
#define GUARD_BATTLE_CARD_H

#include <cstdint>

struct BattleCard {
	uint16_t card_id;
	bool is_face_down = false;
	bool can_evolve = false;
};

#endif // GUARD_BATTLE_CARD_H