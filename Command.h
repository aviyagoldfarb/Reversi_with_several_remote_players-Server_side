//
// Created by udi on 24/12/17.
//

#ifndef EX5_SERVER_COMMAND_H
#define EX5_SERVER_COMMAND_H

#include <vector>
#include <string>
#include "Server.h"

using namespace std;

class Command {
    public:
        virtual void execute(vector<string> args, Server server) = 0;
        virtual ~Command() {}
};

#endif //EX5_SERVER_COMMAND_H
