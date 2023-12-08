#include "room.h"

// Room constructor
Room::Room(bool reserved, int size, int number, int cost)
{
    reservationStatus = reserved;
    roomSize = size;
    roomNumber = number;
    roomCost = cost;
}

void Room::setReservation(bool reservation)
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