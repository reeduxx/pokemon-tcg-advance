#ifndef DECK_H
#define DECK_H

constexpr int MAX_DECK_SIZE = 60;

#include "bn_vector.h"
#include "battle_card.h"
#include "card.h"
#include "decks.h"
class Hand;

struct CardInstance {
	uint16_t card_id;
	bool is_face_down = false;
	bool is_tapped = false;
};

using Deck = bn::vector<BattleCard, MAX_DECK_SIZE>;

void shuffle_deck(Deck& deck);
void draw_card(Deck& deck, Hand& hand);
void load_deck_id(DeckId id, Deck& deck);

#endif // DECK_H