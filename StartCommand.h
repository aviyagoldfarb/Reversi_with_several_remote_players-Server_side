//
// Created by udi on 24/12/17.
//

#ifndef EX5_SERVER_STARTCOMMAND_H
#define EX5_SERVER_STARTCOMMAND_H

#include "Command.h"
#include <iostream>
#include <map>


class StartCommand : public Command {
public:
    StartCommand();
    ~StartCommand();
    virtual void execute(vector<string> args, Server server,  vector<Game>* games, int clientSocket);
};


#endif //EX5_SERVER_STARTCOMMAND_H
