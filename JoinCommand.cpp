//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "JoinCommand.h"
#include <cstring>

JoinCommand::JoinCommand() {}

void JoinCommand::execute(vector<string> args, Server server,  vector<Game>* gamesPtr, int clientSocket) {
    char buffer[3];
    memset(buffer, '\0', 3);
    pthread_mutex_t count_mutex;

    for (int i = 0; i < gamesPtr->size(); i++) {
        if ((!args[0].compare((*gamesPtr)[i].name)) && ((*gamesPtr)[i].whiteClientSocket == 0)) {
            //joined the game, write 1 to the client
            strcpy(buffer, "1");
            server.writeToClient(clientSocket, buffer);
            (*gamesPtr)[i].whiteClientSocket = clientSocket;
            pthread_mutex_lock(&count_mutex);
            //delete the game from the gamesPtr vector
            gamesPtr->erase(gamesPtr->begin() + i);
            pthread_mutex_unlock(&count_mutex);
            server.twoClientsCommunication((*gamesPtr)[i].blackClientSocket, (*gamesPtr)[i].whiteClientSocket);
            return;
        }
    }
    //cant join this game, write -1 to the client
    strcpy(buffer, "-1");
    server.writeToClient(clientSocket, buffer);
}