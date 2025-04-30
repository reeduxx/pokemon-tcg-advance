#ifndef GUARD_BATTLE_CARD_H
#define GUARD_BATTLE_CARD_H

#include <cstdint>
#include "bn_vector.h"

struct BattleCard {
	uint16_t card_id;
	bool is_face_down = false;
	bool can_evolve = false;
	bn::vector<uint16_t, 8> energy;
};

#endif // GUARD_BATTLE_CARD_H