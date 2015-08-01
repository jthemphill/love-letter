#ifndef ACTION_H
#define ACTION_H

#include "const.h"

struct Action {
    Card card_;

    Action(Card card)
      : card_(card) {}
};

struct TargetedAction : Action {
    int targetPlayer_;

    TargetedAction(Card card, int targetPlayer)
      : Action(card), targetPlayer_(targetPlayer) {}
};

struct GuardAction : TargetedAction {
    Card cardNamed_;

    GuardAction(int targetPlayer, Card cardNamed)
      : TargetedAction(GUARD, targetPlayer), cardNamed_(cardNamed) {}
};

#endif // ACTION_H
