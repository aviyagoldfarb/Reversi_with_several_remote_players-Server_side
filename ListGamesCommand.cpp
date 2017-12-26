//
// Created by udi on 25/12/17.
//

#include "ListGamesCommand.h"

ListGamesCommand ::ListGamesCommand() {}

void ListGamesCommand ::printListOfOpenGames(void *listOfOpenGames) {
    vector<string>* loogP = (vector<string>*)listOfOpenGames;
    vector<string> loog = *loogP;
    for (int i = 0; i < loog.size(); i++) {
        cout << loog[i] << endl;
    }
}