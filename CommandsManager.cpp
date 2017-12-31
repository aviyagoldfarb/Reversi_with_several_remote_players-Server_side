//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "CommandsManager.h"
#include "StartCommand.h"
#include "JoinCommand.h"
#include "ListGamesCommand.h"
#include <cstdlib>

CommandsManager::CommandsManager(Server server) : server(server) {
    commandsMap["start"] = new StartCommand();
    commandsMap["list_games"] = new ListGamesCommand();
    commandsMap["join"] = new JoinCommand();
}

void CommandsManager::executeCommand(string command, vector<string> args, int clientSocket) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args, server, &games, clientSocket);
}

void CommandsManager::startServer() {
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    pthread_t thread;
    threads.push_back(thread);
    int rc = pthread_create(&threads[0], NULL, acceptClientsFromServer, NULL);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }
    threads.pop_back();

    pthread_exit(NULL);

}

void* CommandsManager::acceptClientsFromServer(void*) {
    while (true) {
        int clientSocket = server.acceptClients();

        pthread_t thread;
        threads.push_back(thread);
        int sizeOfThreads = threads.size();
        int rc = pthread_create(&threads[sizeOfThreads], NULL, getCommandFromServer, (void *) clientSocket);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }
        pthread_exit(NULL);
        threads.pop_back();
    }
}

void* CommandsManager:: getCommandFromServer(void* clientSocket) {
    CommandOrder* cop;
    CommandOrder co;
    bool stay = true;
    while(stay) {
        (void *) cop = server.getCommand((int) clientSocket);
        co = *cop;
        if ((!co.command.compare("join")) || (!co.command.compare("start")) || (!co.command.compare("list_games"))) {
            this->executeCommand(co.command, co.args, (int) clientSocket);
            if ((!co.command.compare("join")) ||(!co.command.compare("start"))) {
                stay = false;
            }
        }
    }
}


CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}
