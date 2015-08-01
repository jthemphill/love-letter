#ifndef BOT_H
#define BOT_H

#include "events.h"
#include "const.h"

class Bot {
 public:
    virtual ~Bot() {}

    virtual void addEvent(const Event& event) = 0;
    virtual const Action* makeChoice(Card hand_card, Card drawn_card) = 0;
};

#endif // BOT_H
