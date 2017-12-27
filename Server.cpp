//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define MAX_CONNECTED_CLIENTS 10

using namespace std;


Server::Server(int port) :port(port), serverSocket(0) {
    cout << "Server" << endl;
}

void Server::start() {
    //Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }

    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
}

int Server::acceptClients() {

    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;

    // looping until two clients create communication
    //while (true) {

        cout << "Waiting for clients connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (clientSocket == -1)
            throw "Error on accept client";
    return clientSocket;
   // }
}

void Server::twoClientsCommunication(int blackClientSocket, int whiteClientSocket) {
        int black = 1;
        int white = 2;
        int n;
        n = write(blackClientSocket, &black, sizeof(black));
        if (n == -1) {
            cout << "Error writing to blackClientSocket" << endl;
            return;
        }

        n = write(whiteClientSocket, &white, sizeof(white));
        if (n == -1) {
            cout << "Error writing to whiteClientSocket" << endl;
            return;
        }

        // the game
        handleClients(blackClientSocket, whiteClientSocket);

        // Close communication with the current clients
        close(blackClientSocket);
        close(whiteClientSocket);


}

// Handle requests from a specific client
void Server::handleClients(int blackClientSocket, int whiteClientSocket) {
    int x, y;

    while (true) {
        int n;

        //getting the chosen cell of the black player.
        Point blackPlayerChosenCell = this->readCell(blackClientSocket);

        if (blackPlayerChosenCell.getX() == -1 && blackPlayerChosenCell.getY() == -1) {
            return;
        }


        cout << "Got cell: ";
        blackPlayerChosenCell.pointToPrint();
        cout << endl;


        x = blackPlayerChosenCell.getX();
        y = blackPlayerChosenCell.getY();

        // write the result back to the white client
        n = write(whiteClientSocket, &x, sizeof(x));
        if (n == -1) {
            cout << "Error writing to whiteClientSocket" << endl;
            return;
        }
        n = write(whiteClientSocket, &y, sizeof(y));
        if (n == -1) {
            cout << "Error writing to whiteClientSocket" << endl;
            return;
        }

        //getting the chosen cell of the white player.
        Point whitePlayerChosenCell = this->readCell(whiteClientSocket);

        if (whitePlayerChosenCell.getX() == -1 && whitePlayerChosenCell.getY() == -1) {
            return;
        }


        cout << "Got cell: ";
        whitePlayerChosenCell.pointToPrint();
        cout << endl;


        x = whitePlayerChosenCell.getX();
        y = whitePlayerChosenCell.getY();

        // Write the result back to the black client
        n = write(blackClientSocket, &x, sizeof(x));
        if (n == -1) {
            cout << "Error writing to blackClientSocket" << endl;
            return;
        }
        n = write(blackClientSocket, &y, sizeof(y));
        if (n == -1) {
            cout << "Error writing to blackClientSocket" << endl;
            return;
        }

    }

}

void Server::stop() {
    close(serverSocket);
}

Point Server::readCell(int client) {
    Point chosenCell(-1, -1);
    int x, y;
    int n;

    n = read(client, &x, sizeof(x));
    if (n == -1) {
        cout << "Error reading the chosen cell" << endl;
        return chosenCell;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return chosenCell;
    }

    n = read(client, &y, sizeof(y));
    if (n == -1) {
        cout << "Error reading the chosen cell" << endl;
        return chosenCell;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return chosenCell;
    }

    chosenCell.setX(x);
    chosenCell.setY(y);

    return chosenCell;
}

void* Server::getCommand(int clientSocket) {
    char* s[200], command;
    int n;
    vector<string> args;
    CommandOrder co;

    n = read(clientSocket, &s, sizeof(s));
    if (n == -1) {
        cout << "Error reading the command" << endl;
        return (void*)1;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return (void*)1;
    }

    //dividing the scanning to the command and the arguments

    co.command = command;
    co.args = args;
    CommandOrder* cop;
    return (void*)cop;
}

void Server :: writeToClient(int clientSocket, string whatToWrite) {
    int n;
    // Write the result back to the black client
    n = write(clientSocket, &whatToWrite, sizeof(whatToWrite));
    if (n == -1) {
        cout << "Error writing to clientSocket" << endl;
        return;
    }
    return;
}