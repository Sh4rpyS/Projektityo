#pragma once

class Room
{
public:
    // Constructor
    Room(bool reserved, int size, int number, int cost, int time);

    // Gets the room variables
    bool getRoomReserveStatus();
    bool getRoomOwner();
    int getRoomNumber();
    int getRoomCost();
    int getRoomSize();
    int getRoomTime();

    // Used to change the room variables
    void setRoomCost(int cost);
    void setRoomTime(int time);
    void setRoomReservation(bool reservation);
    void setRoomOwner(bool userIsOwner);

private:

    // Room variables
    bool reservationStatus { false };
    bool ownedByUser { false };
    int roomSize { 0 };
    int roomCost { 0 };
    int roomNumber { 0 };
    int roomTime { 0 };
};