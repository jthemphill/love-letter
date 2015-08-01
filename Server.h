#ifndef SERVER_H
#define SERVER_H

#include <random>
#include <vector>

#include "Round.h"

class Server {

public:
    int game(int nplayers, std::default_random_engine& rng, bool verbose);
    int round(int num_players, int starting_player,
              std::default_random_engine& rng,
              const int tokens[], bool verbose);
};

#endif // SERVER_H
