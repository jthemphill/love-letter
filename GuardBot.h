#ifndef GUARD_BOT_H
#define GUARD_BOT_H

#include <vector>

#include "Bot.h"
#include "Random.h"
#include "events.h"

/**
 * GuardBot always plays the lower card, like GreedyBot.
 * But it will only name cards that haven't been played yet.
 */
class GuardBot : public Bot {
    const PublicInfo& info_;
    int player_;
    Random random_;

    std::vector<const Event*> events_;

    Card chooseCardToName(Card hand_card, Card drawn_card);

public:
    GuardBot(const PublicInfo& info, int seed, int player);
    void addEvent(const Event& event);
    const Action* makeChoice(Card hand_card, Card drawn_card);
};

#endif // GREEDY_BOT_H
