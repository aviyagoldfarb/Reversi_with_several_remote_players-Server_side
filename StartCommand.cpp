//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "StartCommand.h"

StartCommand :: StartCommand() {}

void StartCommand ::execute(vector<string> args, Server server, vector<Game> *gamesp, int clientSocket) {
    vector<Game> games = *gamesp;
    pthread_mutex_t count_mutex;
    for (int i = 0; i < games.size(); i++) {
        if (!args[0].compare(games[i].name)) {
            server.writeToClient(clientSocket, "-1");//write -1 to the client
            return;
        }
    }
    Game game;
    game.name = args[0];
    game.blackClientSocket = clientSocket;
    game.whiteClientSocket = 0;

    pthread_mutex_lock(&count_mutex);
    games.push_back(game);
    pthread_mutex_unlock(&count_mutex);

    server.writeToClient(clientSocket, "1");//write to the client that it's done.
    return;
}