#ifndef SERVER_HPP
#define SERVER_HPP

#include <random>
#include <vector>

#include "Round.h"

class Server {

public:
    int game(int starting_player, int nplayers, bool verbose);
    int round(int starting_player, int num_players, bool verbose = false);
};

#endif // SERVER_HPP
