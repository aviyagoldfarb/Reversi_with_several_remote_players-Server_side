//
// Created by udi on 28/12/17.
//

#ifndef EX5_SERVER_JOINCOMMAND_H
#define EX5_SERVER_JOINCOMMAND_H


#include "Command.h"
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <map>



class JoinCommand : public Command {
    public:
    JoinCommand();
    ~JoinCommand();
    virtual void execute(vector<string> args, Server server,  vector<Game>* games, int clientSocket);

};


#endif //EX5_SERVER_JOINCOMMAND_H
