#pragma once

class Room
{
public:
    Room(bool reserved, int size, int number); // Constructor

    void changeReservation(bool reservation);

    bool getRoomReserveStatus();
    int getRoomNumber();
    int getRoomCost();
    int getRoomSize();

private:
    bool reserveStatus { false };
    
    int roomSize { 0 };
    int roomCost { 0 };
    int roomNumber { 0 };
};