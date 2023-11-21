#pragma once

class Room
{
public:
    Room(bool reserved, int roomSize); // Constructor

private:
    bool reserved { false };
    int roomSize { 0 };
    int roomCost { 0 };
};