#ifndef CARD_NAMES_H
#define CARD_NAMES_H

#include <cstdint>
#include "card_name_ids.h"

const char* get_card_name(CardName name_id);
extern const uint16_t CARD_NAME_COUNT;

#endif // CARD_NAMES_H