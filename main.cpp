#include <cstdio>
#include <vector>

#include "Env.hpp"
#include "RandomBot.hpp"
#include "Server.hpp"

int main() {
    Server server;
    server.round(0, 4, true);

    int winners[4] = { 0 };
    for (int i = 0; i < 1000; ++i) {
        ++winners[server.round(0, 4, false)];
    }

    for (int i = 0; i < 4; ++i) {
        printf("Player %d won %d times.\n", i, winners[i]);
    }

    return 0;
}
