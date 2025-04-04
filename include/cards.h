#ifndef GUARD_CARDS_H
#define GUARD_CARDS_H

#include <cstdint>
#include "card.h"

extern const Card cards[];
extern const uint16_t CARD_DATABASE_SIZE;

const Card* get_card_by_id(uint16_t id);

#endif // GUARD_CARDS_H