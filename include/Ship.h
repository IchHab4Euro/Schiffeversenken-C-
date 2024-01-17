#ifndef SHIP_H //sollen wir das so überal machen?
#define SHIP_H

#include "Board.h"
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
    void setFieldSegment(std::vector<FieldSegment*> fieldSegments);
    Direction shipDirection;

private:
    std::string name;
    int length;
    int id; 
    std::vector<FieldSegment*> fieldSegments;
    
    static int nextId; 
};
#endif