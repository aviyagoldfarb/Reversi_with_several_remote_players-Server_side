//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "Server.h"
#include "CommandsManager.h"
#include <stdlib.h>
#include <fstream>

using namespace std;

int main() {
    int port;
    ifstream inFile;
    inFile.open("server_configuration_file.txt");

    if (inFile.is_open()) {
        inFile >> port;
        inFile.close();
    }
    else cout << "Unable to open file";

    Server server(port);
    CommandsManager commandsManager(server);
    commandsManager.startServer();

}