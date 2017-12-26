//
// Created by udi on 25/12/17.
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
    virtual void execute(vector<string> args, vector<string> listOfOpenGames) {
        pthread_t thread;
        int rc = pthread_create(&thread, NULL, printListOfOpenGames, void* listOfOpenGames);
        if (rc) {
            cout << "Error: unable to create thread of print list of games, " << rc << endl;
            exit(-1);
        }
        pthread_exit(NULL);
    }
    void printListOfOpenGames(void* server);

};




#endif //EX5_SERVER_LISTGAMESCOMMAND_H
