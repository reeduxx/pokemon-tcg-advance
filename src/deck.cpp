#include "bn_random.h"
#include "battle_card.h"
#include "deck.h"

void shuffle_deck(Deck& deck) {
	bn::random rand;
	
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