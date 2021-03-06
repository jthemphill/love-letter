#ifndef PUBLIC_INFO_H
#define PUBLIC_INFO_H

#include <vector>

#include "choice.h"
#include "events.h"
#include "const.h"

struct PublicInfo {
    int turn_;
    int activePlayer_;
    int totalPlayers_;
    int deckSize_;
    int tokens_[4];
    bool handmaiding_[4];
    bool live_[4];
    History history_;

    void nextPlayer();

    PublicInfo(int nplayers, int starting_player, const int tokens[]);

    bool legalMove(const Choice& choice) const;
    bool legalTarget(int current_player, const TargetedAction& action) const;
    int livePlayers() const;
    int targetablePlayers() const;
    bool canTarget(int player) const;
    int sumCards(int player) const;

    friend class Env;
};

#endif // PUBLIC_INFO_H
