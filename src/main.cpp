#include "bn_core.h"
#include "bn_keypad.h"
#include "battle_manager.h"
#include "rng.h"

int main() {
    bn::core::init();
	BattleManager battle_manager;
	int seed = 0;
	
	while(!bn::keypad::start_pressed()) {
		++seed;
		bn::core::update();
	}

	RNG::instance().seed(seed);
	
    while(true) {
		battle_manager.update();
        bn::core::update();
    }
}
