#include <cstdio>
#include <vector>

#include "Round.h"
#include "RandomBot.h"
#include "Server.h"

int main() {
    Server server;
    server.round(0, 4, true);

    int scores[4] = { 0 };
    for (int i = 0; i < 10000; ++i) {
        std::vector<int> winners = server.round(0, 4, false);

        for (int p : winners) {
            ++scores[p];
        }
    }

    for (int i = 0; i < 4; ++i) {
        printf("Player %d won %d times.\n", i, scores[i]);
    }

    return 0;
}
