#ifndef RANDOM_H
#define RANDOM_H

#include <random>

#include "const.h"
#include "PublicInfo.h"

class Random {
    std::default_random_engine rng_;

public:
    Random(int seed);
    bool coinflip(int chance = 2);
    int roll(int min, int max);
    Card card(bool include_guard);
    int target(const PublicInfo& env, int player, bool include_self);
};

#endif // RANDOM_H
