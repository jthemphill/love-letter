#ifndef ROUND_H
#define ROUND_H

#include <vector>

#include "const.h"
#include "PublicInfo.h"

class Round {
    PublicInfo info_;
    int turn_;
    Card hands_[4];
    Card deck_[16];
    Card burn_;
    Card drawn_;
    bool verbose_;

    void discard(History& events, int source_player, int target_player);
    Card drawCard();
    void killPlayer(History& events, int player);
    int sumCards(int player) const;

public:
    Round(int nplayers, int starting_player,
          std::default_random_engine rng, const int tokens[],
          bool verbose = false);

    const PublicInfo& getPublicInfo() const;
    bool isOver() const;
    int getWinner() const;
    void printHands() const;
    void printDeck() const;

    Choice startTurn();
    bool completeTurn(History& history, const Choice& choice);
    void resolveTargetedAction(History& events, int player,
                               const TargetedAction& action);
};

#endif // ROUND_H
