#include "Random.hpp"

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

int Random::target(const PublicInfo& env, int player, bool include_self) {
    std::uniform_int_distribution<> die(include_self ? 0 : 1,
                                        env.livePlayers() - 1);

    int roll = die(rng_);

    int p = player;
    do {
        if (env.canTarget(p)) {
            if (roll == 0) {
                return p;
            }

            --roll;
        }

        p = (p + 1) % env.totalPlayers_;
    } while (p != player);

    if (!include_self && p == player) {
        return -1;
    }

    return p;
}
