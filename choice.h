#ifndef CHOICE_H
#define CHOICE_H

#include "const.h"
#include "actions.h"
#include "choice.h"

struct Choice {
    int turn_;
    int player_;
    Card holding_;
    Card drawn_;
    const Action* action_;

    Choice(int turn, int player, Card holding, Card drawn);
    Choice(int turn, int player, Card holding, Card drawn,
           const Action* action);

    void print() const;
};

#endif // CHOICE_H
