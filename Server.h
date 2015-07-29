#ifndef SERVER_HPP
#define SERVER_HPP

#include <random>
#include <vector>

#include "Round.h"

class Server {

public:
    std::vector<int> round(int starting_player, int num_players, bool verbose = false);
};

#endif // SERVER_HPP
