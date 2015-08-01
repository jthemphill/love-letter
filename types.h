#ifndef TYPES_H
#define TYPES_H

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

#endif // TYPES_H
