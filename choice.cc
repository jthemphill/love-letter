#include <cstdio>

#include "choice.h"
#include "const.h"

Choice::Choice(int turn, int player, Card holding, Card drawn)
    : turn_(turn), player_(player), holding_(holding), drawn_(drawn),
      action_(NULL) {}

Choice::Choice(int turn, int player, Card holding, Card drawn,
               const Action* action)
    : turn_(turn), player_(player), holding_(holding), drawn_(drawn),
      action_(action) {}


void Choice::print() const {
    printf(
        "Player %d had [%s, %s], played %s",
        player_,
        name_of_card(holding_),
        name_of_card(drawn_),
        name_of_card(action_->card_));

    int target = NOBODY;
    switch (action_->card_) {
    case GUARD:
    case PRIEST:
    case BARON:
    case PRINCE:
    case KING:
    {
        const TargetedAction& targeted_action = *((const TargetedAction*) action_);
        target = targeted_action.targetPlayer_;
        if (target == NOBODY) {
            printf(" but could not find a letter to tamper with.\n");
            return;
        }
    }
        break;
    default:
        break;
    }

    switch (action_->card_) {
    case GUARD:
    {
        const GuardAction& guard_action = *((const GuardAction*) action_);
        printf(" and claimed player %d has a %s.\n", target,
               name_of_card(guard_action.cardNamed_));

        break;
    }
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
