//
// Created by udi on 24/12/17.
//

#ifndef EX5_SERVER_COMMANDSMANAGER_H
#define EX5_SERVER_COMMANDSMANAGER_H

#include <map>
#include "Command.h"
#include "Server.h"


class CommandsManager {
public: CommandsManager(Server server);
    ~CommandsManager();
    void executeCommand(string command, vector<string> args);
private:
    map<string, Command *> commandsMap;
    Server server;
};


#endif //EX5_SERVER_COMMANDSMANAGER_H
