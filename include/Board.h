#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"
#include "BoardSegment.h"
#include <iostream>
#include <vector>

class Board {

public:
    Board();
    void init(std::vector<Ship*> ships);
    virtual void placeShips() = 0;
    int getBoardSize();
    BoardSegment* grid[10][10]; //nicht 10 fest sondern irgendwie über die BoardSize
    
protected:
    Direction numberToDirection(int number) const;
    int cordinateToLatitude(const std::string cordinate) const;
    int cordinateToLongitude(const std::string cordinate) const;
    bool checkForColission() const;
    void replaceShipPlacement(BoardSegment::FieldState newState);
    bool placeShip(int latitude, int longitude, Direction direction, Ship* ship);

    std::vector<Ship*> shipsNextToBoard;
    std::vector<Ship*> shipsOnBoard;
     
private:
    int const boardSize = 10;
    
    //Sammlung aller Spielfelder ungeordnet
};
#endif