//
// Created by udi on 24/12/17.
//

#ifndef EX5_SERVER_COMMANDSMANAGER_H
#define EX5_SERVER_COMMANDSMANAGER_H

#include <map>
#include "Command.h"
#include "Server.h"
struct CommandOrder {
    string command;
    vector<string> args;
};


class CommandsManager {
public:
    CommandsManager(Server server);
    ~CommandsManager();
    void executeCommand(string command, vector<string> args, int clientSocket);
    void startServer();
    void* acceptClientsFromServer(void*);
    void* getCommandFromServer(void*);
private:
    map<string, Command *> commandsMap;
    Server server;
    vector<pthread_t> threads;

    vector<Game> games;
};

#endif //EX5_SERVER_COMMANDSMANAGER_H
