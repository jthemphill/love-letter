#include <random>

#include "Random.h"

Random::Random() {
    std::random_device rd;
    rng_ = std::default_random_engine(rd());
}

bool Random::coinflip(int chance) {
    if (chance <= 0) {
        return false;
    }

    std::uniform_int_distribution<> die(0, chance - 1);
    return die(rng_) == 0;
}

Card Random::card(bool include_guard) {
    if (include_guard) {
        std::uniform_int_distribution<> cards(GUARD, PRINCESS);
        return Card(cards(rng_));
    } else {
        std::uniform_int_distribution<> cards(PRIEST, PRINCESS);
        return Card(cards(rng_));
    }
}

int Random::roll(int min, int max) {
    std::uniform_int_distribution<> die(min, max);
    return die(rng_);
}

int Random::target(const PublicInfo& env, int player, bool include_self) {
    int targetable_players = env.targetablePlayers();
    if (!include_self && env.canTarget(player)) {
        --targetable_players;
    }

    if (targetable_players <= 0) {
        return NOBODY;
    }

    std::uniform_int_distribution<> die(0, targetable_players - 1);
    int roll = die(rng_);

    int p = 0;
    while (true) {
        if (!env.canTarget(p) || (!include_self && p == player)) {
            ++p;
            continue;
        }

        if (roll == 0) {
            break;
        }

        --roll;
        ++p;
    }

    return p;
}
