#include <random>

#include "Random.h"

Random::Random(int seed): rng_(seed) {
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

int Random::winningTarget(const PublicInfo& env, int player) {
    int targetable_players = env.targetablePlayers();
    if (env.canTarget(player)) {
        --targetable_players;
    }

    if (targetable_players <= 0) {
        return NOBODY;
    }

    int num_ties = 0;
    int max_tokens = -1;
    for (int i = 0; i < env.totalPlayers_; ++i) {
        if (i == player || !env.canTarget(i) || env.tokens_[i] < max_tokens) {
            continue;
        }

        if (env.tokens_[i] > max_tokens) {
            num_ties = 0;
            max_tokens = env.tokens_[i];
        } else {
            ++num_ties;
        }
    }

    std::uniform_int_distribution<> die(0, num_ties);
    int roll = die(rng_);

    for (int i = 0; i < env.totalPlayers_; ++i) {
        if (i == player || !env.canTarget(i) || env.tokens_[i] < max_tokens) {
            continue;
        }

        if (roll == 0) {
            return i;
        }

        --roll;
    }

    throw std::logic_error("Reached the end of the function");
}
