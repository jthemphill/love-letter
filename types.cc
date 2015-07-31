#include <cstdio>

#include "types.h"

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
    case PRIEST:
    case BARON:
    case KING:
        if (target < 0) {
            printf(" but could not find a letter to tamper with.\n");
            return;
        }
        break;
    default:
        break;
    }

    switch (action_.card_) {
    case GUARD:
        printf(" and claimed player %d has a %s.\n", target, name_of_card(action_.cardNamed_));
        break;
    case PRIEST:
        printf(" and looked at player %d's hand.\n", target);
        break;
    case BARON:
        printf(" and compared hands with player %d.\n", target);
        break;
    case HANDMAID:
        printf(" and got protection for a turn.\n");
        break;
    case PRINCE:
        printf(" and forced player %d to discard and draw.\n", target);
        break;
    case KING:
        printf(" and traded hands with player %d.\n", target);
        break;
    default:
        printf(".\n");
        break;
    }
}
