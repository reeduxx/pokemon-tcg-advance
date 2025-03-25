#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_items_card_sheet_1.h"

int main()
{
    bn::core::init();
	constexpr int max_index = 3;
	int current_index = 0;
	bn::sprite_ptr card = bn::sprite_items::card_sheet_1.create_sprite(0, 0, current_index);

    while(true) {
		if(bn::keypad::left_pressed()) {
			current_index--;
			
			if(current_index < 0) {
				current_index = max_index;
			}
			
			card.set_tiles(bn::sprite_items::card_sheet_1.tiles_item(), current_index);
		}
		
		else if(bn::keypad::right_pressed()) {
			current_index++;
			
			if(current_index > max_index) {
				current_index = 0;
			}
			
			card.set_tiles(bn::sprite_items::card_sheet_1.tiles_item(), current_index);
		}
		
        bn::core::update();
    }
}
