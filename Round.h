#ifndef ROUND_HPP
#define ROUND_HPP

#include <vector>

#include "types.h"
#include "PublicInfo.h"

class Round {
    PublicInfo env_;
    int turn_;
    Card hands_[4];
    Card deck_[16];
    Card burn_;
    Card drawn_;
    bool verbose_;

    void discard(int source_player, int target_player);
    Card drawCard();
    void killPlayer(int player);
    int sumCards(int player) const;

public:
    Round(int starting_player, int num_players, bool verbose = false);

    const PublicInfo& getPublicInfo() const;
    bool isOver() const;
    int getWinner() const;
    void printHands() const;
    void printDeck() const;

    Choice startTurn();
    bool completeTurn(const Choice& action);
};

#endif // ROUND_HPP
