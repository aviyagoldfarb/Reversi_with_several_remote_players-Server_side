//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "ListGamesCommand.h"
#include <cstring>

ListGamesCommand ::ListGamesCommand() {}

void ListGamesCommand::execute(vector<string> args, Server server,  vector<Game>* gamesPtr, int clientSocket) {
    char gamesListBuffer[250];
    memset(gamesListBuffer, '\0', 250);
    int counter = 0;
    pthread_mutex_t count_mutex;
    for (int i = 0; i < gamesPtr->size(); i++) {
        if (((*gamesPtr)[i].blackClientSocket != 0) && ((*gamesPtr)[i].whiteClientSocket = 0)) {
            strcat(gamesListBuffer, (*gamesPtr)[i].name.c_str());
        }
        strcat(gamesListBuffer, " ");
    }
    server.writeToClient(clientSocket, gamesListBuffer);
}