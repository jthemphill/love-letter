#include "Server.h"
#include "RandomBot.h"

#include <vector>

constexpr int MAX_POINTS(int nplayers) {
    return 12 / nplayers + 1;
}

int Server::game(int starting_player, int nplayers, bool verbose) {
    int scores[nplayers];
    for (int i = 0; i < nplayers; ++i) {
        scores[i] = 0;
    }

    int nrounds = 1;
    while (true) {
        if (verbose) {
            printf("=== ROUND %d ===\n", nrounds);
        }

        int winner = round(starting_player, nplayers, verbose);
        ++scores[winner];

        if (verbose) {
            printf("Scores: \n");
            for (int i = 0; i < nplayers; ++i) {
                printf("Player %d: %d\n", i, scores[i]);
            }
            printf("\n");
        }

        if (scores[winner] == MAX_POINTS(nplayers)) {
            if (verbose) {
                printf("=== PLAYER %d WINS ===\n\n", winner);
            }
            return winner;
        }

        starting_player = winner;
        ++nrounds;
    }
}

int Server::round(int starting_player, int num_players, bool verbose) {
    Round round(starting_player, num_players, verbose);

    const PublicInfo& info = round.getPublicInfo();

    std::vector<RandomBot> bots;
    for (int i = 0; i < 4; ++i) {
        bots.emplace_back(info, i);
    }

    int turn = 0;
    if (verbose) {
        printf("\n== Turn %d ==\n", turn);
        round.printHands();
    }
    int i = 0;
    while (!round.isOver() && i < 16) {
        if (info.turn_ > turn) {
            turn = info.turn_;
            if (verbose) {
                printf("\n== Turn %d ==\n", turn);
                round.printHands();
            }
        }

        int j = 0;
        Choice choice = round.startTurn();
        choice.action_ = bots[info.activePlayer_].makeChoice(choice);

        if (verbose) {
            choice.print();
        }

        if (!round.completeTurn(choice)) {
            printf("Player %d tried to make an illegal move!\n",
                   info.activePlayer_);
            exit(1);
        }
    }

    int winner = round.getWinner();
    if (verbose) {
        printf("Player %d wins.\n\n", winner);
    }

    return winner;
}
