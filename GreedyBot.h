#ifndef GREEDY_BOT_H
#define GREEDY_BOT_H

#include "Bot.h"
#include "Random.h"

/**
 * GreedyBot always plays the lower card.
 * It's not any smarter than that, though.
 */
class GreedyBot : public Bot {
    const PublicInfo& info_;
    int player_;
    Random random_;

public:
    GreedyBot(const PublicInfo& info, int seed, int player);
    void addEvent(const Event& event);
    const Action* makeChoice(Card hand_card, Card drawn_card);
};

#endif // GREEDY_BOT_H
