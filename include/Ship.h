#ifndef SHIP_H //sollen wir das so überal machen?
#define SHIP_H

#include "BoardSegment.h"
#include <string>
#include <vector>

enum class Direction {North, East, South, West};

class Ship {
public:
    Ship(std::string name, int length);
    std::string getName() const;
    int getLength() const;
    int getId() const;
    bool isShipSunk() const;
    void setBoardSegment(std::vector<BoardSegment*> BoardSegments);
    Direction shipDirection;

private:
    std::string name;
    int length;
    int id; 
    std::vector<BoardSegment*> BoardSegments;
    
    static int nextId; 
};
#endif