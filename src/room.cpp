#include "room.h"

// Room constructor
Room::Room(bool reserved, int roomSize)
{
    reserved = reserved;
    roomSize = roomSize;
}

void Room::changeReservation(bool reservation)
{
    reserved = reservation;
}