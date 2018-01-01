//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX4_SERVER_SERVER_H
#define EX4_SERVER_SERVER_H

#include "Point.h"
#include <vector>

struct CommandOrder {
    string command;
    vector<string> args;
};

class Server {
public:
    Server(int port);
    void start();
    int acceptClient();
    void writeToClient(int clientsocket, char* buffer);
    CommandOrder* getCommand(int clientSocket);
    void twoClientsCommunication(int blackClientSocket, int whiteClientSocket);
    void handleClients(int blackClientSocket, int whiteClientSocket);
    Point readCell(int client);
    void stop();

private:
    int port;
    // the socket's file descriptor
    int serverSocket;
};

#endif //EX4_SERVER_SERVER_H
