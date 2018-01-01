//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX5_SERVER_COMMANDSMANAGER_H
#define EX5_SERVER_COMMANDSMANAGER_H

#include <map>
#include "Command.h"
#include "Server.h"


class CommandsManager {
public:
    CommandsManager(Server server);
    void executeCommand(string command, vector<string> args, int clientSocket);
    void startServer();
    void* acceptClientsFromServer(void* args);
    void* getAndExecuteCommandFromServer(void*);
    ~CommandsManager();
private:
    Server server;
    map<string, Command *> commandsMap;
    vector<pthread_t> threads;
    vector<Game> games;
};

#endif //EX5_SERVER_COMMANDSMANAGER_H
