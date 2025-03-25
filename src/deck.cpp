#include "bn_random.h"
#include "deck.h"

void shuffle_deck(Deck& deck) {
	for(int i = 0; i < deck.size(); ++i) {
		int j = bn::random::get_int(deck.size());
		bn::swap(deck[i], deck[j]);
	}
}

void draw_card(Deck& deck, bn::vector<CardInstance, 10>& hand) {
	if(deck.empty() || hand.full()) {
		return;
	}
	
	hand.push_back(deck.back());
	deck.pop_back();
}