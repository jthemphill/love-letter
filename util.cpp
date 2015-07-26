#include <random>

#include "util.hpp"
#include "types.hpp"
#include "Env.hpp"

Card randomCard(std::mt19937 rng, bool include_guard) {
    if (include_guard) {
        std::uniform_int_distribution<> cards(GUARD, PRINCESS);
        return Card(cards(rng));
    } else {
        std::uniform_int_distribution<> cards(PRIEST, PRINCESS);
        return Card(cards(rng));
    }
}

int randomTarget(const PublicEnv& env, int player, std::mt19937 rng, bool include_self) {
    std::uniform_int_distribution<> die(include_self ? 0 : 1,
                                        env.livePlayers() - 1);

    int roll = die(rng);

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

bool countessCaught(Card maybe_countess, Card maybe_royalty) {
    if (maybe_countess != COUNTESS) {
        return false;
    }

    switch (maybe_royalty) {
    case PRINCE:
    case KING:
        return true;
    default:
        return false;
    }
}
