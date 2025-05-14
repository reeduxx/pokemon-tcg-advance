#include <bn_core.h>
#include <bn_cstdlib.h>
#include <bn_keypad.h>
#include "bn_regular_bg_items_pokemon_logo.h"
#include "battle_manager.h"
#include "rng.h"

void titlescreen() {
	bn::regular_bg_ptr bg = bn::regular_bg_items::pokemon_logo.create_bg(0, 0);
	
	while(!bn::keypad::start_pressed()) {
		bn::core::update();
	}

	bg.set_visible(false);
}

int main() {
    bn::core::init();
	int seed = 0;
	titlescreen();

	while(!bn::keypad::start_pressed()) {
		++seed;
		bn::core::update();
	}

	RNG::instance().seed(0x41C64E6D * seed + 0x0000303B);
	BattleManager battle_manager;

    while(true) {
		battle_manager.update();
		RNG::instance().update();
        bn::core::update();
    }
}
