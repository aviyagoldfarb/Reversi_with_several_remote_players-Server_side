//
// Created by udi on 24/12/17.
//

#include "CommandsManager.h"
#include "StartCommand.h"


CommandsManager::CommandsManager(Server server)
        : server(server) {
    commandsMap["start"] = new StartCommand();
// Add more commands...
}
void CommandsManager::executeCommand(string command, vector<string> args) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args, server);
}
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}
