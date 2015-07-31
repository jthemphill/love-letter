#include <cstdio>
#include <vector>

#include "Round.h"
#include "RandomBot.h"
#include "Server.h"

const int NGAMES = 10000;

int main() {
    Server server;
    server.game(0, 4, true);

    printf("\nRunning %d games.\n", NGAMES);
    int scores[4] = { 0 };
    for (int i = 0; i < NGAMES; ++i) {
        int winner = server.game(0, 4, false);
        ++scores[winner];
    }

    for (int i = 0; i < 4; ++i) {
        printf("Player %d won %d times.\n", i, scores[i]);
    }

    return 0;
}
