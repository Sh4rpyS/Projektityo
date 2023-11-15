#pragma once

#include <iostream>
#include <map>
#include <string>
#include <tuple>

#include "room.h"

class Application {
public:
    void start();
    void stop();

    void printWelcomeMessage();
    void printMessage(std::string message);

    std::string printAndGetUserInput(std::map<int, std::tuple<std::string, std::string>> inputOptions);
    void processUserInput(std::string userInput);

    bool getRunState();
    
    std::string getMenuState();
    void setMenuState(std::string state);

private:
    // Will contain all the rooms in a list
    // First value is the room ID, and the second value stores the memory address of the room
    std::map<int, Room*> rooms;
    const int roomCount { 100 };
    
    // If this is false, the application will close
    bool runState { true };

    std::string menuState { "start" };
};