#include "bn_core.h"
#include "battle.h"
#include "cursor.h"
#include "cursor_controller.h"

int main() {
    bn::core::init();
	Battle battle;
	Cursor cursor;
	CursorController cursor_controller(cursor, battle);
	
    while(true) {
		cursor_controller.update();
		cursor.update();
		battle.update();
        bn::core::update();
    }
}
