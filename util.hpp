#ifndef UTIL_H
#define UTIL_H

#include "types.hpp"
#include "Env.hpp"

#include <random>

Card randomCard(std::mt19937 rng, bool include_guard);
int randomTarget(const PublicEnv& env, int player, std::mt19937 rng, bool include_self);
bool countessCaught(Card maybe_countess, Card maybe_royalty);

#endif // UTIL_H
