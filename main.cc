#include <cstdio>
#include <cstring>
#include <random>
#include <vector>

#include "Round.h"
#include "RandomBot.h"
#include "Server.h"

const int NPLAYERS = 4;
const int NGAMES = 100;

int main(int argc, char **argv) {
    bool verbose = false;
    if (argc >= 2 && !strncmp(argv[1], "-v", 2)) {
        verbose = true;
    }

    std::random_device rd;
    std::default_random_engine rng(rd());

    Server server;
    server.game(NPLAYERS, rng, verbose);

    printf("\nRunning %d games.\n", NGAMES);
    int scores[4] = { 0 };
    for (int i = 0; i < NGAMES; ++i) {
        int winner = server.game(NPLAYERS, rng, false);
        ++scores[winner];
    }

    for (int i = 0; i < NPLAYERS; ++i) {
        printf("Player %d won %d times.\n", i, scores[i]);
    }

    return 0;
}
