#ifndef DECK_H
#define DECK_H

#include "bn_vector.h"
#include "card.h"

constexpr int MAX_DECK_SIZE = 60;

struct CardInstance {
	uint16_t card_id;
	bool is_face_down = false;
	bool is_tapped = false;
};

using Deck = bn::vector<CardInstance, MAX_DECK_SIZE>;

void shuffle_deck(Deck& deck);
void draw_card(Deck& deck, bn::vector<CardInstance, 10>& hand);

#endif // DECK_H