#include "Server.h"
#include "RandomBot.h"

#include <vector>

std::vector<int> Server::round(int starting_player, int num_players, bool verbose) {
    Round game(starting_player, num_players, verbose);

    const PublicInfo& info = game.getPublicInfo();

    std::vector<RandomBot> bots;
    for (int i = 0; i < 4; ++i) {
        bots.emplace_back(info, i);
    }

    int turn = 0;
    if (verbose) {
        printf("\n== Turn %d ==\n", turn);
        game.printHands();
    }
    int i = 0;
    while (!game.isOver() && i < 16) {
        if (info.turn_ > turn) {
            turn = info.turn_;
            if (verbose) {
                printf("\n== Turn %d ==\n", turn);
                game.printHands();
            }
        }

        int j = 0;
        Choice choice = game.startTurn();
        choice.action_ = bots[info.activePlayer_].makeChoice(choice);

        if (verbose) {
            choice.print();
        }

        if (!game.completeTurn(choice)) {
            printf("Player %d tried to make an illegal move!\n",
                   info.activePlayer_);
            exit(1);
        }
    }

    std::vector<int> winners = game.getWinner();
    if (verbose) {
        if (winners.size() == 1) {
            printf("Player %d wins.\n", winners[0]);
        } else {
            printf("Tie! Players ");
            printf("%d", winners[0]);
            for (int i = 1; i < winners.size() - 1; ++i) {
                printf(", %d", winners[i]);
            }

            printf(" and %d win.\n", winners[winners.size() - 1]);
        }
    }

    return winners;
}
