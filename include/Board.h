#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"
#include "BoardSegment.h"
#include <iostream>
#include <vector>

enum class Direction {North, East, South, West};

class Board {

public:
    Board();
    void init(std::vector<Ship*> initShips);
    virtual void placeShips() = 0;
    virtual void attack(Board* board) = 0; 
    int getBoardSize();
    BoardSegment* grid[10][10]; //nicht 10 fest sondern irgendwie über die BoardSize
    void setSunkenShips();
    bool allShipsSunk() const;

protected:
    Direction numberToDirection(int number) const;
    int cordinateToLatitude(const std::string cordinate) const;
    int cordinateToLongitude(const std::string cordinate) const;
    bool checkForColission();
    void replaceShipPlacement(SegmentState newState, Ship* shipToPlace);
    bool placeShip(int latitude, int longitude, Direction direction, Ship* ship);
    int const boardSize = 10;
    

    std::vector<Ship*> shipsNextToBoard;
    std::vector<Ship*> shipsOnBoard;
     
private:
    
    
    //Sammlung aller Spielfelder ungeordnet
};
#endif