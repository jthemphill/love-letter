#include "Server.h"
#include "Bot.h"
#include "GreedyBot.h"
#include "GuardBot.h"
#include "RandomBot.h"

#include <stdexcept>
#include <vector>

constexpr int max_tokens(int nplayers) {
    return 12 / nplayers + 1;
}

int Server::game(int nplayers, std::default_random_engine& rng, bool verbose) {
    std::uniform_int_distribution<> player_roll(0, nplayers - 1);
    int starting_player = player_roll(rng);

    int tokens[nplayers];
    for (int i = 0; i < nplayers; ++i) {
        tokens[i] = 0;
    }

    int nrounds = 1;
    while (true) {
        if (verbose) {
            printf("=== ROUND %d ===\n", nrounds);
        }

        int winner = round(nplayers, starting_player, rng, tokens, verbose);
        ++tokens[winner];

        if (verbose) {
            printf("Scores: \n");
            for (int i = 0; i < nplayers; ++i) {
                printf("Player %d: %d\n", i, tokens[i]);
            }
            printf("\n");
        }

        if (tokens[winner] == max_tokens(nplayers)) {
            if (verbose) {
                printf("=== PLAYER %d WINS ===\n\n", winner);
            }
            return winner;
        }

        starting_player = winner;
        ++nrounds;
    }
}

int Server::round(int nplayers, int starting_player,
                  std::default_random_engine& rng,
                  const int tokens[], bool verbose) {
    History history;
    Round round(nplayers, starting_player, rng, tokens, verbose);

    if (verbose) {
        printf("Deck:\n");
        round.printDeck();
    }

    const PublicInfo& info = round.getPublicInfo();

    Bot* bots[nplayers];
    bots[0] = new GreedyBot(info, rng(), 0);
    bots[1] = new GuardBot(info, rng(), 1);
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
            for (int j = 0; j < nplayers; ++j) {
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

    for (int i = 0; i < nplayers; ++i) {
        delete bots[i];
    }

    for (const Event* e : history) {
        delete e;
    }

    return winner;
}
