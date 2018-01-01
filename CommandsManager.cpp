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
    string exitStr;
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, acceptClientsFromServer, NULL);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }
    //wait for 'exit' command
    cin >> exitStr;
    if (!(exitStr.compare("exit"))){
        server.stop();

        pthread_exit(NULL);
    }

}

void* CommandsManager::acceptClientsFromServer(void* args) {
    int clientSocket;
    while (true) {
        clientSocket = server.acceptClient();
        pthread_t thread;
        threads.push_back(thread);
        int numberOfThreads = threads.size()-1;
        int rc = pthread_create(&threads[numberOfThreads], NULL, getAndExecuteCommandFromServer, (void *) clientSocket);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }
        //pthread_exit(NULL);
        //threads.pop_back();
    }
}

void* CommandsManager:: getAndExecuteCommandFromServer(void* clientSocket) {
    CommandOrder* coPtr;
    bool gameNotPlayed = true;
    while(gameNotPlayed) {
        coPtr = server.getCommand((int) clientSocket);
        if ((!coPtr->command.compare("join")) || (!coPtr->command.compare("start")) || (!coPtr->command.compare("list_games"))) {
            this->executeCommand(coPtr->command, coPtr->args, (int) clientSocket);
            if ((!coPtr->command.compare("join")) || (!coPtr->command.compare("start"))) {
                gameNotPlayed = false;
            }
        }
    }
    threads.pop_back();
}


CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}
