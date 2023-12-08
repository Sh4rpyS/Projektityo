#pragma once

#include <iostream>

// General usage (Lists and stuff)
#include <map>
#include <string>
#include <tuple>

// Needed for the random
#include <stdlib.h>
#include <ctime>

#include "room.h"

class Application {
public:
    void start();

private:
    void update();
    void stop();

    void printWelcomeMessage();
    void printMessage(std::string message);

    std::map<int, std::tuple<std::string, std::string>> inputOptions;

    std::string printAndGetUserInput(std::map<int, std::tuple<std::string, std::string>> inputOptions);
    void processUserInput(std::string userInput);

    bool getRunState();

    int getWorkNumber();
    void setWorkNumber(int number);
    
    std::string getMenuState();
    void setMenuState(std::string state);

    // Will contain all the rooms in a list
    // First value is the room ID, and the second value stores the memory address of the room
    std::map<int, Room*> rooms;
    
    // If this is false, the application will close
    bool runState { false };

    int randomWorkNumber { 0 };
    long balance { 0 };
    int day { 0 };
    int workDone { 0 };

    std::string menuState { " " };

    void createRooms(int randomRoomCount);

    int roomCount { 0 };
    int reservedRooms { 0 };
    int freeRooms { 0 };

    int getRoomCount();
    int getReservedRoomCount();
    int getFreeRoomCount();

    int page { 0 };
    int maxPage { 0 };
    int selectableRooms[300] = {};
    int selectableRoomCount { 0 };
    int selectedRoom { -1 };
    void getRooms(bool reserveStatus, int roomSize);
    
};