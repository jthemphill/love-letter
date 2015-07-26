#ifndef RANDOM_BOT_HPP
#define RANDOM_BOT_HPP

#include <random>

#include "types.hpp"
#include "Env.hpp"
#include "Random.hpp"

struct RandomBot {
    Random random_;

    const PublicInfo& env_;
    int player_;

    RandomBot(const PublicInfo& env, int player);

    Action makeChoice(const Choice& choice);
};

#endif // RANDOM_BOT_HPP
