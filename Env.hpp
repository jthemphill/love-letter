#ifndef ENV_HPP
#define ENV_HPP

#include <vector>

#include "types.hpp"

struct PublicInfo {
    int turn_;
    int activePlayer_;
    int totalPlayers_;
    int deckSize_;
    int tokens_[4];
    bool live_[4];

    PublicInfo(int starting_player, int num_players);

    bool legalMove(const Choice& choice) const;
    int livePlayers() const;
    void nextPlayer();
    bool canTarget(int player) const;
    Card lastCardPlayed(int player) const;
};

class Env {
    PublicInfo env_;
    Card hands_[4];
    Card deck_[16];
    Card burn_;
    Card drawn_;
    bool verbose_;
    std::vector<Choice> history_;

    void discard(int player);
    Card drawCard();
    void killPlayer(int player);

public:
    Env(int starting_player, int num_players, bool verbose = false);

    const PublicInfo& getPublicInfo() const;
    int winner() const;
    void printHands() const;
    void printDeck() const;

    Choice startTurn();
    bool completeTurn(const Choice& action);
};

#endif // ENV_HPP
