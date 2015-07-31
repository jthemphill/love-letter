#ifndef PUBLIC_INFO_HPP
#define PUBLIC_INFO_HPP

#include <vector>

#include "events.h"
#include "types.h"

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

    PublicInfo(int starting_player, int num_players);

    bool legalMove(const Choice& choice) const;
    int livePlayers() const;
    int targetablePlayers() const;
    bool canTarget(int player) const;
    int sumCards(int player) const;

    friend class Env;
};

#endif // PUBLIC_INFO_HPP
