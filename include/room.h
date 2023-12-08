#pragma once

class Room
{
public:
    // Constructor
    Room(bool reserved, int size, int number, int cost);

    // Gets the room variables
    bool getRoomReserveStatus();
    int getRoomNumber();
    int getRoomCost();
    int getRoomSize();

    // Used to change the room variables
    void setRoomCost(int cost);
    void setRoomTime(int time);
    void setReservation(bool reservation);

private:

    // Room variables
    bool reservationStatus { false };
    int roomSize { 0 };
    int roomCost { 0 };
    int roomNumber { 0 };
    int roomTime { 0 };
};