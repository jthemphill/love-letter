#include "RandomBot.h"
#include "Random.h"
#include "types.h"

RandomBot::RandomBot(const PublicInfo& env, int player)
    : info_(env), player_(player) {}

void RandomBot::addEvent(const Event* event) {
}

const Action* RandomBot::makeChoice(Card hand_card, Card drawn_card) {
    Card card_played;
    if (countess_caught(hand_card, drawn_card)) {
        card_played = hand_card;
    } else if (countess_caught(drawn_card, hand_card)) {
        card_played = drawn_card;
    } else {
        card_played = random_.coinflip(2) ? hand_card : drawn_card;
    }

    int target = NOBODY;
    Card card_named = UNKNOWN;

    switch (card_played) {
    case GUARD:
        card_named = random_.card(false);
        target = random_.target(info_, player_, false);
        return new GuardAction(target, card_named);
    case PRIEST:
    case BARON:
    case KING:
        target = random_.target(info_, player_, false);
        return new TargetedAction(card_played, target);
    case PRINCE:
        target = random_.target(info_, player_, true);
        return new TargetedAction(card_played, target);
    default:
        return new Action(card_played);
    }
}
