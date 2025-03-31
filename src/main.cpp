#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_fixed_point.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_items_playmat.h"
#include "bn_sprite_items_card_back.h"
#include "bn_sprite_items_card_sheet_1.h"
#include "bn_sprite_items_cursor.h"
#include "cursor.h"
#include "cursor_controller.h"
#include "playmat.h"

int main() {
    bn::core::init();
	Playmat playmat;
	Cursor cursor;
	CursorController cursor_controller(cursor, playmat);
	int i = 0;
	
	auto decrement([&] {
		return --i % playmat.zone_count();
	});
	
	auto increment([&] {
		return ++i % playmat.zone_count();
	});
	
    while(true) {
		cursor_controller.update();
		cursor.update();
		playmat.update();
		
		/*
		if(bn::keypad::left_pressed()) {
			cursor.set_pos(playmat.get_zone(decrement()).pos);
		}
		
		if(bn::keypad::right_pressed()) {
			cursor.set_pos(playmat.get_zone(increment()).pos);
		}
		
		if(bn::keypad::up_held()) {
			if(cursor.position().y() <= -71) {
				playmat.scroll_to_opponent();
				cursor.set_pos(bn::fixed_point(cursor.position().x(), 71));
			}
			
			cursor.move_by(0, -1);
		}
		
		if(bn::keypad::down_held()) {
			if(cursor.position().y() >= 71) {
				playmat.scroll_to_player();
				cursor.set_pos(bn::fixed_point(cursor.position().x(), -71));
			}
			
			cursor.move_by(0, 1);
		}
		*/
		
        bn::core::update();
    }
}
