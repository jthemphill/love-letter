#include "RandomBot.hpp"
#include "Random.hpp"

RandomBot::RandomBot(const PublicInfo& env, int player)
    : env_(env), player_(player) {}

Action RandomBot::makeChoice(const Choice& choice) {
    Card hand_card = choice.holding_;
    Card drawn_card = choice.drawn_;

    Card card_played;
    if (countessCaught(hand_card, drawn_card)) {
        card_played = hand_card;
    } else if (countessCaught(drawn_card, hand_card)) {
        card_played = drawn_card;
    } else {
        card_played = random_.coinflip(2) ? hand_card : drawn_card;
    }

    int target = -1;
    Card card_named = UNKNOWN;

    switch (card_played) {
    case GUARD:
        card_named = random_.card(false);
        // FALLTHROUGH
    case PRIEST:
    case BARON:
    case KING:
        target = random_.target(env_, player_, false);
        break;
    case PRINCE:
        target = random_.target(env_, player_, true);
        break;
    default:
        break;
    }

    return Action(card_played, true, target, card_named);
}
