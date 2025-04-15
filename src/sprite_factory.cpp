#include "bn_sprite_items_card_back.h"
#include "bn_sprite_items_card_sheet_1.h"
#include "bn_sprite_items_card_sheet_2.h"
#include "bn_sprite_items_card_sheet_3.h"
#include "bn_sprite_items_energy_sheet_1.h"
#include "bn_sprite_items_energy_sheet_2.h"
#include "bn_sprite_items_energy_sheet_3.h"
#include "cards.h"
#include "sprite_factory.h"

bn::sprite_ptr SpriteFactory::create_sprite(const BattleCard& card, const bn::fixed_point& pos, bool is_opponent) {
    if(card.is_face_down) {
        bn::sprite_ptr sprite = bn::sprite_items::card_back.create_sprite(pos);
        
        if(is_opponent) sprite.set_vertical_flip(true);

        return sprite;
    }

    const Card* data = get_card_by_id(card.card_id);

    if(!data) return bn::sprite_items::card_back.create_sprite(pos);
    if(data->header.type == CardType::CARD_POKEMON) return create_pokemon_sprite(data->pokemon.primary_type, pos, is_opponent);
    if(data->header.type == CardType::CARD_TRAINER) return create_trainer_sprite(pos, is_opponent);
    if(data->header.type == CardType::CARD_ENERGY) return create_energy_sprite(data->energy.element, pos, is_opponent);
}

bn::sprite_ptr SpriteFactory::create_pokemon_sprite(Type type, const bn::fixed_point& pos, bool is_opponent) {
    bn::sprite_ptr sprite = bn::sprite_items::card_back.create_sprite();
    
    if(type == Type::TYPE_GRASS) sprite = bn::sprite_items::card_sheet_1.create_sprite(pos, 0);
    if(type == Type::TYPE_FIRE) sprite = bn::sprite_items::card_sheet_1.create_sprite(pos, 1);
    if(type == Type::TYPE_WATER) sprite = bn::sprite_items::card_sheet_1.create_sprite(pos, 2);
    if(type == Type::TYPE_LIGHTNING) sprite = bn::sprite_items::card_sheet_1.create_sprite(pos, 3);
    if(type == Type::TYPE_FIGHTING) sprite = bn::sprite_items::card_sheet_2.create_sprite(pos, 0);
    if(type == Type::TYPE_PSYCHIC) sprite = bn::sprite_items::card_sheet_2.create_sprite(pos, 1);
    if(type == Type::TYPE_COLORLESS) sprite = bn::sprite_items::card_sheet_2.create_sprite(pos, 2);
    if(type == Type::TYPE_DARKNESS) sprite = bn::sprite_items::card_sheet_2.create_sprite(pos, 3);
    if(type == Type::TYPE_METAL) sprite = bn::sprite_items::card_sheet_3.create_sprite(pos, 0);
    if(is_opponent) sprite.set_horizontal_flip(true);

    return sprite;
}

bn::sprite_ptr SpriteFactory::create_trainer_sprite(const bn::fixed_point& pos, bool is_opponent) {
    bn::sprite_ptr sprite = bn::sprite_items::card_sheet_3.create_sprite(pos, 1);

    if(is_opponent) sprite.set_horizontal_flip(true);
    
    return sprite;
}

bn::sprite_ptr SpriteFactory::create_energy_sprite(Type type, const bn::fixed_point& pos, bool is_opponent) {
    bn::sprite_ptr sprite = bn::sprite_items::card_back.create_sprite();

    if(type == Type::TYPE_GRASS) sprite = bn::sprite_items::energy_sheet_1.create_sprite(pos, 0);
    if(type == Type::TYPE_FIRE) sprite = bn::sprite_items::energy_sheet_1.create_sprite(pos, 1);
    if(type == Type::TYPE_WATER) sprite = bn::sprite_items::energy_sheet_1.create_sprite(pos, 2);
    if(type == Type::TYPE_LIGHTNING) sprite = bn::sprite_items::energy_sheet_1.create_sprite(pos, 3);
    if(type == Type::TYPE_FIGHTING) sprite = bn::sprite_items::energy_sheet_2.create_sprite(pos, 0);
    if(type == Type::TYPE_PSYCHIC) sprite = bn::sprite_items::energy_sheet_2.create_sprite(pos, 1);
    if(type == Type::TYPE_COLORLESS) sprite = bn::sprite_items::energy_sheet_2.create_sprite(pos, 2);
    if(type == Type::TYPE_DARKNESS) sprite = bn::sprite_items::energy_sheet_2.create_sprite(pos, 3);
    if(type == Type::TYPE_METAL) sprite = bn::sprite_items::energy_sheet_3.create_sprite(pos, 0);
    if(is_opponent) sprite.set_horizontal_flip(true);

    return sprite;
}