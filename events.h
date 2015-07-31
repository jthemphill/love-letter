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
};

struct DiscardEvent : Event {
    Event::Types type_;
    int turn_;

    int sourcePlayer_;
    int targetPlayer_;
    Card cardDiscarded_;

    DiscardEvent(int turn, int source_player, int target_player, Card card_discarded)
      : type_(Event::DISCARD), turn_(turn), sourcePlayer_(source_player),
        targetPlayer_(target_player), cardDiscarded_(card_discarded) {}
};

struct DeathEvent : Event {
    Event::Types type_;
    int turn_;

    int deadPlayer_;
    Card lastCardInHand_;

    DeathEvent(int turn, int deadPlayer, Card lastCardInHand)
      : type_(Event::DEATH), turn_(turn), deadPlayer_(deadPlayer),
        lastCardInHand_(lastCardInHand) {}
};

struct ActionEvent : Event {
    Event::Types type_;
    int turn_;

    int sourcePlayer_;
    Action action_;

    ActionEvent(int turn, int sourcePlayer, const Action& action)
        : type_(Event::ACTION), turn_(turn), sourcePlayer_(sourcePlayer),
          action_(action) {}
};

struct RevealedEvent : Event {
    Event::Types type_;
    int turn_;

    int sourcePlayer_;
    int targetPlayer_;
    Card cardRevealed_;

    RevealedEvent(int turn, int sourcePlayer, int targetPlayer,
                  Card cardRevealed)
        : type_(Event::REVEALED), turn_(turn), sourcePlayer_(sourcePlayer),
          targetPlayer_(targetPlayer),
          cardRevealed_(cardRevealed) {}
};

#endif // EVENTS_H
