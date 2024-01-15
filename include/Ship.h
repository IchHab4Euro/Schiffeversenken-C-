#ifndef SHIP_H //sollen wir das so überal machen?
#define SHIP_H

#include <string>
#include <vector>

struct ShipSegment {
    enum class ShipState {Hit, NoHit};
    ShipSegment();
    void hit();
    bool isHit() const;
    ShipState shipState;
};

class Ship {
public:
    Ship(std::string name, int length);
    std::string getName() const;
    int getLength() const;
    int getId() const;
    bool isShipSunk() const;

private:
    enum class Direction {North, East, South, West};
    std::string name;
    int length;
    int id;
    Direction shipDirection; 
    std::vector<ShipSegment> shipComponents;
    
    static int nextId; 
};
#endif