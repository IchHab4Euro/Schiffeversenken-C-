#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"

#include <iostream>
#include <vector>

struct BoardField {
    enum class FieldState {Ship, ShipPlacement, Water}
    BoardField();
    void setShipState(ShipSegment shipSegment);
    FieldState fieldState;
    ShipSegment shipSegment;
};

class Board {

public:
    Board(int boardSize);
    ~Board();
    void printBoard() const;
    virtual void placeShips() = 0;
    
protected:
    Direction numberToDirection(int number) const;
    int cordinateToLatitude(const std::string cordinate) const;
    int cordinateToLongitude(const std::string cordinate) const;
    bool checkForColission() const;
    void changeBoardFieldState(BoardFieldState newState);
    bool placeShip(int latitude, int longitude, Direction direction, Ship ship);

    std::vector<Ship> shipsNextToBoard;
    std::vector<Ship> shipsOnBoard;
    BoardField grid[10][10]; //nicht 10 fest sondern irgendwie über die BoardSize
    int boardSize;
     

private:
    void setupBoard();
    void setupShips();
    
    //Sammlung aller Spielfelder ungeordnet

    std::string gameID = "1";
    std::string playerID = "1";
    char splitSymbol = ';';
    

};
#endif