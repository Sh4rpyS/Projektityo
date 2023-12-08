#include "room.h"

// Room constructor
Room::Room(bool reserved, int size, int number, int cost, int time)
{
    reservationStatus = reserved;
    roomSize = size;
    roomNumber = number;
    roomCost = cost;
    roomTime = time;
}

// Sets the reservation status for the room
void Room::setRoomReservation(bool reservation)
{
    reservationStatus = reservation;
}

// Sets the cost for the room
void Room::setRoomCost(int cost)
{
    roomCost = cost;
}

// Sets the reservation time for the room
void Room::setRoomTime(int time)
{
    roomTime = time;
}

// Gets the room reservation status
bool Room::getRoomReserveStatus()
{
    return reservationStatus;
}

// Gets the room number
int Room::getRoomNumber()
{
    return roomNumber;
}

// Gets the room cost
int Room::getRoomCost()
{
    return roomCost;
}

// Gets the room size
int Room::getRoomSize()
{
    return roomSize;
}

// Gets the room reservation time
int Room::getRoomTime()
{
    return roomTime;
}

// Returns whether the room is owned by the user or the randoms
bool Room::getRoomOwner()
{
    return ownedByUser;
}

// Sets the room owner to be the user
void Room::setRoomOwner(bool userIsOwner)
{
    ownedByUser = userIsOwner;
}