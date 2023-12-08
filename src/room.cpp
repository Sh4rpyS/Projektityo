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

void Room::setRoomReservation(bool reservation)
{
    reservationStatus = reservation;
}

void Room::setRoomCost(int cost)
{
    roomCost = cost;
}

void Room::setRoomTime(int time)
{
    roomTime = time;
}

bool Room::getRoomReserveStatus()
{
    return reservationStatus;
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

int Room::getRoomTime()
{
    return roomTime;
}

bool Room::getRoomOwner()
{
    return ownedByUser;
}

void Room::setRoomOwner(bool userIsOwner)
{
    ownedByUser = userIsOwner;
}