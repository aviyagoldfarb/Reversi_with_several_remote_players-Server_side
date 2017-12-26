cmake_minimum_required(VERSION 3.8)
project(ex5_server)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Server.cpp Server.h Point.cpp Point.h Command.h CommandsManager.cpp CommandsManager.h ListGamesCommand.cpp ListGamesCommand.h StartCommand.cpp StartCommand.h)
add_executable(ex5_server ${SOURCE_FILES})