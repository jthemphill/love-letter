#include "Server.h"
#include "Bot.h"
#include "GreedyBot.h"
#include "GuardBot.h"
#include "RandomBot.h"

#include <stdexcept>
#include <vector>

constexpr int MAX_POINTS(int nplayers) {
    return 12 / nplayers + 1;
}

int Server::game(int nplayers, std::default_random_engine& rng, bool verbose) {
    std::uniform_int_distribution<> player_roll(0, nplayers - 1);
    int starting_player = player_roll(rng);

    int scores[nplayers];
    for (int i = 0; i < nplayers; ++i) {
        scores[i] = 0;
    }

    int nrounds = 1;
    while (true) {
        if (verbose) {
            printf("=== ROUND %d ===\n", nrounds);
        }

        int winner = round(starting_player, rng, nplayers, verbose);
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

int Server::round(int starting_player, std::default_random_engine& rng,
                  int num_players, bool verbose) {
    History history;
    Round round(starting_player, num_players, rng, verbose);

    if (verbose) {
        printf("Deck:\n");
        round.printDeck();
    }

    const PublicInfo& info = round.getPublicInfo();

    Bot* bots[num_players];
    bots[0] = new GreedyBot(info, rng(), 0);
    bots[1] = new GreedyBot(info, rng(), 1);
    for (int i = 2; i < 4; ++i) {
      bots[i] = new RandomBot(info, rng(), i);
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

        Choice choice = round.startTurn();
        choice.action_ = bots[info.activePlayer_]->makeChoice(choice.holding_,
                                                              choice.drawn_);

        if (verbose) {
            choice.print();
        }

        History events;
        if (!round.completeTurn(events, choice)) {
            printf("Player %d tried to make an illegal move!\n",
                   info.activePlayer_);
            throw std::logic_error("Aborting.");
        }

        for (const Event* e : events) {
            history.push_back(e);
            for (int j = 0; j < num_players; ++j) {
                if (e->type_ != Event::REVEALED || info.activePlayer_ == j) {
                    bots[j]->addEvent(*e);
                }
            }
        }
    }

    int winner = round.getWinner();
    if (verbose) {
        printf("Player %d wins.\n\n", winner);
    }

    for (int i = 0; i < num_players; ++i) {
        delete bots[i];
    }

    for (const Event* e : history) {
        delete e;
    }

    return winner;
}
