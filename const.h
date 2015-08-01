#ifndef CONST_H
#define CONST_H

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

constexpr int QUANTITIES[9] = {
    /* UNKNOWN */ -1,
    /* GUARD */    5,
    /* PRIEST */   2,
    /* BARON */    2,
    /* HANDMAID */ 2,
    /* PRINCE */   2,
    /* KING */     1,
    /* COUNTESS */ 1,
    /* PRINCESS */ 1,
};

const int NOBODY = -1;

constexpr int quantity(Card c) {
    return QUANTITIES[int(c)];
}

inline const char* name_of_card(Card c) {
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
    default:
        return 0;
    }
}

inline bool countess_caught(Card maybe_countess, Card maybe_royalty) {
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

#endif // CONST_H
