#include "bn_core.h"
#include "bn_seed_random.h"
#include "battle_card.h"
#include "deck.h"

void shuffle_deck(Deck& deck) {
	bn::seed_random rand(bn::core::current_cpu_ticks());
	
	for(int i = 0; i < deck.size(); ++i) {
		int j = rand.get_unbiased_int(deck.size());
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