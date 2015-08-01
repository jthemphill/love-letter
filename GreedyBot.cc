#include "GreedyBot.h"
#include "PublicInfo.h"
#include "const.h"

GreedyBot::GreedyBot(const PublicInfo& info, int player)
    : info_(info), player_(player) {}

void GreedyBot::addEvent(const Event& event) {}

const Action* GreedyBot::makeChoice(Card hand_card, Card drawn_card) {
    if (countess_caught(hand_card, drawn_card) ||
        countess_caught(drawn_card, hand_card)) {
        return new Action(COUNTESS);
    }

    Card lower_card;
    if (hand_card <= drawn_card) {
        lower_card = hand_card;
    } else {
        lower_card = drawn_card;
    }

    int target;
    switch (lower_card) {
    case GUARD:
    {
        Card card_named = random_.card(false);
        target = random_.target(info_, player_, false);
        return new GuardAction(target, card_named);
    }
    case PRIEST:
    case BARON:
    case KING:
    {
        int target = random_.target(info_, player_, false);
        return new TargetedAction(lower_card, target);
    }
    case PRINCE:
    {
        target = random_.target(info_, player_, true);
        return new TargetedAction(lower_card, target);
    }
    default:
        return new Action(lower_card);
    }
}
