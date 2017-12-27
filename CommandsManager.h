//
// Created by udi on 24/12/17.
//

#ifndef EX5_SERVER_COMMANDSMANAGER_H
#define EX5_SERVER_COMMANDSMANAGER_H

#include <map>
#include "Command.h"
#include "Server.h"

class CommandsManager {
public:
    CommandsManager(Server server);
    ~CommandsManager();
    void executeCommand(string command, vector<string> args);
    void startServer();
    void* acceptClientsFromServer(void*);
    void* getCommandFromServer(void*);
private:
    map<string, Command *> commandsMap;
    Server server;
    vector<pthread_t> threads;
    struct CommandOrder {
        string command;
        vector<string> args;
    };
};

#endif //EX5_SERVER_COMMANDSMANAGER_H
