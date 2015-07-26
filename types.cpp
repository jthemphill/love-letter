#include <cstdio>

#include "types.hpp"

int quantity(Card c) {
    switch (c) {
    case UNKNOWN:
        return -1;
    case GUARD:
        return 5;
    case PRIEST:
    case BARON:
    case HANDMAID:
    case PRINCE:
        return 2;
    case KING:
    case COUNTESS:
    case PRINCESS:
        return 1;
    }
}

const char* name_of_card(Card c) {
    switch (c) {
    case UNKNOWN: return "UNKNOWN";
    case GUARD: return "Guard";
    case PRIEST: return "Priest";
    case BARON: return "Baron";
    case HANDMAID: return "Handmaid";
    case PRINCE: return "Prince";
    case KING: return "King";
    case COUNTESS: return "Countess";
    case PRINCESS: return "Princess";
    }
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

void Choice::print() const {
    printf(
        "Player %d had [%s, %s], %s %s",
        player_,
        name_of_card(holding_),
        name_of_card(drawn_),
        action_.played_ ? "played" : "discarded",
        name_of_card(action_.card_));

    if (!action_.played_) {
        printf(".\n");
        return;
    }

    int target = action_.targetPlayer_;
    switch (action_.card_) {
    case GUARD:
        printf(", claiming player %d has %s", target, name_of_card(action_.cardNamed_));
        break;
    case PRIEST:
        printf(", looking at player %d's hand", target);
        break;
    case BARON:
        printf(", comparing hands with player %d", target);
        break;
    case HANDMAID:
        printf(", getting protection for a turn");
        break;
    case PRINCE:
        printf(", forcing player %d to discard and draw", target);
        break;
    case KING:
        printf(", trading hands with %d", target);
        break;
    default:
        break;
    }

    printf(".\n");
}
