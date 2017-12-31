//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "ListGamesCommand.h"

ListGamesCommand ::ListGamesCommand() {}

void ListGamesCommand :: execute(vector<string> args, Server server,  vector<Game>* gamesp, int clientSocket) {
    vector<Game> games = *gamesp;;
    int counter = 0;
    for (int i = 0; i < games.size(); i++) {
        if ((games[i].blackClientSocket != 0) && (games[i].whiteClientSocket = 0)) {
            server.writeToClient(clientSocket, games[i].name);
            counter++;
        }
    }
    if (counter == 0) {
        server.writeToClient(clientSocket, "no games to join");
    }
}