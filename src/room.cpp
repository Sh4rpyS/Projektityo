#include "room.h"

// Room constructor
Room::Room(bool reserved, int size, int number)
{
    reserveStatus = reserved;
    roomSize = size;
    roomNumber = number;
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