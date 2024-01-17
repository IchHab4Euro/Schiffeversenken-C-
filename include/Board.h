#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"
//#include "Output.h"
#include <iostream>
#include <vector>

struct FieldSegment {
    enum class FieldState {Ship, ShipHit, ShipPlacement, Water};
    FieldSegment(FieldState initState);
    FieldState fieldState;
    bool isShip();
    bool isShipHit();
    bool isShipPlacement();
    bool isWater();
};

class Board {

public:
    Board();
    void init(std::vector<Ship*> ships);
    virtual void placeShips() = 0;
    int getBoardSize();
    FieldSegment* grid[10][10]; //nicht 10 fest sondern irgendwie über die BoardSize
    
protected:
    Direction numberToDirection(int number) const;
    int cordinateToLatitude(const std::string cordinate) const;
    int cordinateToLongitude(const std::string cordinate) const;
    bool checkForColission() const;
    void replaceShipPlacement(FieldSegment::FieldState newState);
    bool placeShip(int latitude, int longitude, Direction direction, Ship* ship);

    std::vector<Ship*> shipsNextToBoard;
    std::vector<Ship*> shipsOnBoard;
     
private:
    int const boardSize = 10;
    
    //Sammlung aller Spielfelder ungeordnet
};
#endif