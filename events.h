#ifndef EVENTS_H
#define EVENTS_H

#include "types.h"

struct Event {
    enum Types {
        DISCARD,
        DEATH,
        ACTION,
        REVEALED,
    };

    Types type_;
    int turn_;

    Event(Types type, int turn): type_(type), turn_(turn) {}
};

struct DiscardEvent : Event {
    int sourcePlayer_;
    int targetPlayer_;
    Card cardDiscarded_;

    DiscardEvent(int turn, int source_player, int target_player, Card card_discarded)
      : Event(Event::DISCARD, turn), sourcePlayer_(source_player),
        targetPlayer_(target_player), cardDiscarded_(card_discarded) {}
};

struct DeathEvent : Event {
    int deadPlayer_;
    Card lastCardInHand_;

    DeathEvent(int turn, int deadPlayer, Card lastCardInHand)
      : Event(Event::DEATH, turn), deadPlayer_(deadPlayer),
        lastCardInHand_(lastCardInHand) {}
};

struct ActionEvent : Event {
    int sourcePlayer_;
    Action action_;

    ActionEvent(int turn, int sourcePlayer, const Action& action)
        : Event(Event::ACTION, turn), sourcePlayer_(sourcePlayer),
          action_(action) {}
};

struct RevealedEvent : Event {
    int sourcePlayer_;
    int targetPlayer_;
    Card cardRevealed_;

    RevealedEvent(int turn, int sourcePlayer, int targetPlayer,
                  Card cardRevealed)
        : Event(Event::REVEALED, turn), sourcePlayer_(sourcePlayer),
          targetPlayer_(targetPlayer),
          cardRevealed_(cardRevealed) {}
};

typedef std::vector<const Event*> History;

#endif // EVENTS_H
