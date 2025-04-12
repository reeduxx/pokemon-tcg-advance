#ifndef GUARD_RNG_H
#define GUARD_RNG_H

#include "bn_random.h"
#include "bn_seed_random.h"

class RNG {
    private:
        RNG();
        bn::seed_random _rand;
    public: 
        static RNG& instance();
        void seed(uint32_t seed);
        int get_int(int max);
        int get_int(int min, int max);
        bool chance(int percent);
};

#endif // GUARD_RNG_H