//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "JoinCommand.h"


JoinCommand ::JoinCommand() {}

void JoinCommand :: execute(vector<string> args, Server server,  vector<Game>* gamesp, int clientSocket) {
    vector<Game> games = *gamesp;
    int flag = 0;
    for (int i = 0; i < games.size(); i++) {
        if ((!args[0].compare(games[i].name)) && (flag == 0)) {
            if (games[i].whiteClientSocket != 0) {
                games[i].whiteClientSocket = clientSocket;
                server.twoClientsCommunication(games[i].blackClientSocket, games[i].whiteClientSocket);

                flag = 1;
            }
        }
    }
    if (flag == 0) {
        server.writeToClient(clientSocket, "There is no game with this name");
    }
}