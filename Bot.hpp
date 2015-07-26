#ifndef BOT_HPP
#define BOT_HPP

#include "types.hpp"
#include "Env.hpp"

struct Bot {
    virtual Action makeChoice(const Choice& choice) = 0;

    virtual void observeAfterMove(const Action& last_action) = 0;
};

#endif // BOT_HPP
