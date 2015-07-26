#include <cstdio>
#include <vector>

#include "Env.hpp"
#include "RandomBot.hpp"

int main() {
    Env game(0, 4, true);
    const PublicInfo& info = game.getPublicInfo();

    std::vector<RandomBot> bots;
    for (int i = 0; i < 4; ++i) {
        bots.emplace_back(info, i);
    }

    int turn = 0;
    printf("\n== Turn %d ==\n", turn);
    game.printHands();
    int i = 0;
    while (game.winner() == -1 && i < 16) {
        if (info.turn_ > turn) {
            turn = info.turn_;
            printf("\n== Turn %d ==\n", turn);
            game.printHands();
        }

        int j = 0;
        Choice choice = game.startTurn();
        choice.action_ = bots[info.activePlayer_].makeChoice(choice);
        choice.print();
        if (!game.completeTurn(choice)) {
            printf("Player %d tried to make an illegal move!\n",
                   info.activePlayer_);
            return 1;
        }
    }

    int winner = game.winner();
    printf("Winner is %d.\n", winner);

    return 0;
}
