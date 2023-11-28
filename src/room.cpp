#include "room.h"

// Room constructor
Room::Room(bool reserved, int roomSize, int roomNumber)
{
    reserveStatus = reserved;
    roomSize = roomSize;
    roomNumber = roomNumber;
}

void Room::changeReservation(bool reservation)
{
    reserveStatus = reservation;
}

bool Room::getRoomReserveStatus()
{
    return reserveStatus;
}

int Room::getRoomNumber()
{
    return roomNumber;
}

int Room::getRoomCost()
{
    return roomCost;
}

int Room::getRoomSize()
{
    return roomSize;
}