#ifndef SHIP_H //sollen wir das so überal machen?
#define SHIP_H

#include "ShipSegment.h"
#include <string>
#include <vector>

enum class Direction {
    North,
    East,
    South,
    West
};

class Ship {
public:
    Ship(std::string name, int length);
    std::string getName() const;
    int getLength() const;
    int getId() const;
    bool isShipSunk() const;

private:
    std::string name;
    int length;
    int id;
    std::vector<ShipSegment> shipComponents;
    Direction shipDirection; 

    static int nextId; 
};

#endif