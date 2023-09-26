#include <iostream>
#include <map>
#include <tuple>

#include "room.h"

class Application {
public:
    void start();
    void stop();

    void printWelcomeMessage();
    std::string getStartUserInput();
    void processStartUserInput(std::string userInput);

    bool getRunState();

private:
    // Will contain all the rooms in a list
    // First value is the room ID, and the second value stores the memory address of the room
    std::map<int, Room*> rooms;
    const int roomCount { 100 };
    
    // If this is false, the application will close
    bool runState { true };
};