#ifndef RANDOM_BOT_HPP
#define RANDOM_BOT_HPP

#include <random>

#include "types.hpp"
#include "Env.hpp"
#include "Random.hpp"

class RandomBot {
    Random random_;

    const PublicInfo& env_;
    int player_;

public:
    RandomBot(const PublicInfo& env, int player);

    Action makeChoice(const Choice& choice);
};

#endif // RANDOM_BOT_HPP
