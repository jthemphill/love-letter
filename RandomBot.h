#ifndef RANDOM_BOT_HPP
#define RANDOM_BOT_HPP

#include <random>

#include "Bot.h"
#include "types.h"
#include "Round.h"
#include "Random.h"

class RandomBot : public Bot {
    Random random_;

    const PublicInfo& info_;
    int player_;

public:
    RandomBot(const PublicInfo& info, int player);

    virtual void addEvent(const Event& event);
    virtual Action makeChoice(Card hand_card, Card drawn_card);
};

#endif // RANDOM_BOT_HPP
