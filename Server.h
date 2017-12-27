//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX4_SERVER_SERVER_H
#define EX4_SERVER_SERVER_H

#include "Point.h"
#include <vector>

class Server {
public:
    Server(int port);
    void start();
    void stop();
    void twoClientsCommunication(int blackClientSocket, int whiteClientSocket);
    Point readCell(int client);
    int acceptClients();
    void* getCommand(int clientSocket);

private:
    int port;
    // the socket's file descriptor
    int serverSocket;

    void handleClients(int blackClientSocket, int whiteClientSocket);
    struct CommandOrder {
        string command;
        vector<string> args;
    };
};

#endif //EX4_SERVER_SERVER_H
