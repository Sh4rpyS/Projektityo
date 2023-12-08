#pragma once

class Room
{
public:
    Room(bool reserved, int size, int number, int cost); // Constructor

    void setReservation(bool reservation);

    bool getRoomReserveStatus();
    int getRoomNumber();
    int getRoomCost();
    int getRoomSize();

    void setRoomCost(int cost);
    void setRoomTime(int time);

private:
    bool reservationStatus { false };
    
    int roomSize { 0 };
    int roomCost { 0 };
    int roomNumber { 0 };
    int roomTime { 0 };
};