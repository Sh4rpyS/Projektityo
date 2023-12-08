#include "coreApplication.h"

// Stops the application
void Application::stop()
{
    runState = false;
}

// Gets the application status, whether the application is running or not
bool Application::getRunState()
{
    return runState;
}

// Sets the user's room
void Application::setMenuState(std::string state)
{
    menuState = state;
}

// Gets the room the user is in
std::string Application::getMenuState()
{
    return menuState;
}

// Can be used to change the number used in work
void Application::setWorkNumber(int number)
{
    randomWorkNumber = number;
}

// Returns the work number
int Application::getWorkNumber()
{
    return randomWorkNumber;
}

// Gets the overall room count
int Application::getRoomCount()
{
    return roomCount;
}

// Gets the amount of reserved rooms
int Application::getReservedRoomCount()
{
    return reservedRooms;
}

// Gets the amount of free rooms
int Application::getFreeRoomCount()
{
    return freeRooms;
}