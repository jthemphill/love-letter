#include "Server.hpp"
#include "RandomBot.hpp"

int Server::round(int starting_player, int num_players, bool verbose) {
    Env game(starting_player, num_players, verbose);

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
    while (game.winner() == -1 && i < 16) {
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

    int winner = game.winner();
    if (verbose) {
        printf("Winner is %d.\n", winner);
    }

    return winner;
}
