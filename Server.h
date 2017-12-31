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
    void stop();
    void twoClientsCommunication(int blackClientSocket, int whiteClientSocket);
    Point readCell(int client);
    int acceptClients();
    CommandOrder* getCommand(int clientSocket);
    void writeToClient(int clientsocket, string whatToWrite);

private:
    int port;
    // the socket's file descriptor
    int serverSocket;

    void handleClients(int blackClientSocket, int whiteClientSocket);

};

#endif //EX4_SERVER_SERVER_H
