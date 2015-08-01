#ifndef RANDOM_BOT_H
#define RANDOM_BOT_H

#include <random>

#include "Bot.h"
#include "const.h"
#include "Round.h"
#include "Random.h"

class RandomBot : public Bot {
    Random random_;

    const PublicInfo& info_;
    int player_;

public:
    RandomBot(const PublicInfo& info, int player);

    void addEvent(const Event& event);
    const Action* makeChoice(Card hand_card, Card drawn_card);
};

#endif // RANDOM_BOT_H
