//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "StartCommand.h"

StartCommand :: StartCommand() {}

void StartCommand ::execute(vector<string> args, Server server, vector<Game> *gamesp, int clientSocket) {
    vector<Game> games = *gamesp;
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
    games.push_back(game);
    server.writeToClient(clientSocket, "1");//write to the client that it's done.
    return;
}