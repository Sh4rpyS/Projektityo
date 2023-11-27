#pragma once

class Room
{
public:
    Room(bool reserved, int roomSize); // Constructor

    void changeReservation(bool reservation);

private:
    bool reserved { false };
    
    int roomSize { 0 };
    int roomCost { 0 };
};