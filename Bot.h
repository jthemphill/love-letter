#ifndef BOT_HPP
#define BOT_HPP

#include "events.h"
#include "types.h"

class Bot {
 public:
    virtual ~Bot() {}

    virtual void addEvent(const Event* event) = 0;
    virtual Action makeChoice(Card hand_card, Card drawn_card) = 0;
};

#endif // BOT_HPP
