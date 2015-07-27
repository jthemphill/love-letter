#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>

class Env;

enum Card {
    UNKNOWN = 0,
    GUARD = 1,
    PRIEST = 2,
    BARON = 3,
    HANDMAID = 4,
    PRINCE = 5,
    KING = 6,
    COUNTESS = 7,
    PRINCESS = 8,
};

int quantity(Card c);

const char* name_of_card(Card c);
bool countessCaught(Card maybe_countess, Card maybe_royalty);

struct Action {
    Card card_;
    bool played_;
    int targetPlayer_;
    Card cardNamed_;

    Action()
        : card_(UNKNOWN), played_(false), targetPlayer_(-1),
          cardNamed_(UNKNOWN) {}

    Action(Card card, bool played, int target_player, Card card_named)
        : card_(card), played_(played), targetPlayer_(target_player),
          cardNamed_(card_named) {}
};

struct Choice {
    int turn_;
    int player_;
    Card holding_;
    Card drawn_;
    Action action_;

    Choice()
        : turn_(0), player_(0), holding_(UNKNOWN), drawn_(UNKNOWN), action_() {}

    Choice(int turn, int player, Card holding, Card drawn)
        : turn_(turn), player_(player), holding_(holding), drawn_(drawn),
          action_() {}

    Choice(int turn, int player, Card holding, Card drawn, Action action)
        : turn_(turn), player_(player), holding_(holding), drawn_(drawn),
          action_(action) {}

    void print() const;
};

struct Player {
    int wins_;
    Card card_;
};

struct Event {
    enum Types {
        DISCARD,
        DEATH,
        ACTION,
        ROUND_END,
    };

    Types type_;
    Card reason_;
    Action action_;

    Event(Types type, Card reason);
    Event(Types type, Card reason, const Action& action);
    Event(const Event& event);
};

#endif // TYPES_HPP
