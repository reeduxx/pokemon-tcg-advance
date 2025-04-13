#ifndef GUARD_SPRITE_FACTORY_H
#define GUARD_SPRITE_FACTORY_H

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "battle_card.h"
#include "card.h"

class SpriteFactory {
    public:
        static bn::sprite_ptr create_sprite(const BattleCard& card, const bn::fixed_point& pos, bool is_opponent=false);
    private:
        static bn::sprite_ptr create_pokemon_sprite(Type type, const bn::fixed_point& pos, bool is_opponent);
        static bn::sprite_ptr create_trainer_sprite(const bn::fixed_point& pos, bool is_opponent);
        static bn::sprite_ptr create_energy_sprite(Type type, const bn::fixed_point& pos, bool is_opponent);
};

#endif // GUARD_SPRITE_FACTORY_H