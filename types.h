#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>

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

const int NOBODY = -1;

constexpr int quantity(Card c) {
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

constexpr const char* name_of_card(Card c) {
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

constexpr bool countess_caught(Card maybe_countess, Card maybe_royalty) {
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

#endif // TYPES_HPP
