#ifndef RNG_HPP
#define RNG_HPP

#include <random>

#include "types.h"
#include "PublicInfo.h"

class Random {
    std::default_random_engine rng_;

public:
    Random();
    bool coinflip(int chance = 2);
    Card card(bool include_guard);
    int target(const PublicInfo& env, int player, bool include_self);
};

#endif // RNG_HPP
