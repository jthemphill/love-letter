#ifndef RNG_HPP
#define RNG_HPP

#include <random>

#include "types.hpp"
#include "Env.hpp"

class Random {
    std::mt19937 rng_;

public:
    bool coinflip(int chance = 2);
    Card card(bool include_guard);
    int target(const PublicInfo& env, int player, bool include_self);
};

#endif // RNG_HPP
