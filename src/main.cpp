#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "battle.h"
#include "cursor.h"
#include "cursor_controller.h"
#include "rng.h"

int main() {
    bn::core::init();
	int seed = 0;
	Cursor cursor;
	Battle battle(cursor);
	CursorController cursor_controller(cursor, battle);
	
	while(!bn::keypad::start_pressed()) {
		++seed;
		bn::core::update();
	}

	BN_LOG(seed);
	RNG::instance().seed(seed);

    while(true) {
		cursor_controller.update();
		cursor.update();
		battle.update();
        bn::core::update();
    }
}
