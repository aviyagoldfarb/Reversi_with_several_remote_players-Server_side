//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX5_SERVER_LISTGAMESCOMMAND_H
#define EX5_SERVER_LISTGAMESCOMMAND_H

#include "Command.h"
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <map>



class ListGamesCommand : public Command {
public:
    ListGamesCommand();
    ~ListGamesCommand();
    virtual void execute(vector<string> args, Server server,  vector<Game>* games, int clientSocket);
};




#endif //EX5_SERVER_LISTGAMESCOMMAND_H
