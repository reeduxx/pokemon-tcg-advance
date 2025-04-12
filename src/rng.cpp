#include "rng.h"

RNG::RNG() {}

RNG& RNG::instance() {
    static RNG instance;
    return instance;
}

void RNG::seed(uint32_t seed) {
    _rand.set_seed(seed);
}

int RNG::get_int(int max) {
    return _rand.get_unbiased_int(max);
}

int RNG::get_int(int min, int max) {
    return _rand.get_unbiased_int(min, max);
}

bool RNG::chance(int percent) {
    return _rand.get_unbiased_int(100) < percent;
}