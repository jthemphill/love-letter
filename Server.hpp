#ifndef SERVER_HPP
#define SERVER_HPP

#include "Env.hpp"

class Server {

public:
    int round(int starting_player, int num_players, bool verbose = false);
};

#endif // SERVER_HPP
