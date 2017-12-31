//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX5_SERVER_COMMAND_H
#define EX5_SERVER_COMMAND_H

#include <vector>
#include <string>
#include "Server.h"


using namespace std;

struct Game {
    string name;
    int blackClientSocket = 0;
    int whiteClientSocket = 0;
};

class Command {
    public:
        virtual void execute(vector<string> args, Server server, vector<Game>* games, int clientSocket) = 0;
        virtual ~Command() {}
};

#endif //EX5_SERVER_COMMAND_H
