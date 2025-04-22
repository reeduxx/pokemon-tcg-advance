#include "battle_card.h"
#include "deck.h"
#include "hand.h"
#include "rng.h"

void shuffle_deck(Deck& deck) {
	for(int i = 0; i < deck.size(); ++i) {
		int j = RNG::instance().get_int(deck.size());
		bn::swap(deck[i], deck[j]);
	}
}

void draw_card(Deck& deck, Hand& hand) {
	if(deck.empty() || hand.card_count() >= 10) {
		return;
	}
	
	BattleCard card = deck.back();
	deck.pop_back();
	hand.add_card(card);
}

void load_deck_id(DeckId id, Deck& deck) {
	using namespace Decks;
	
	for(const DeckDef& def : DECKS) {
		if(def.id == id) {
			deck.clear();
			
			for(int i = 0; i < MAX_DECK_SIZE; i++) {
				BattleCard card;
				card.card_id = def.cards[i];
				card.is_face_down = false;
				deck.push_back(card);
			}
			
			break;
		}
	}
}