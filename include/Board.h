#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"
#include "BoardField.h"

#include <iostream>
#include <vector>

class Board {

public:
    Board();
    ~Board();
    void printBoard() const;
    virtual void placeShips() = 0;
    
protected:
    //bool isValidPlacement(int latitude, int longitude, Ship pickedShip) const;
    Direction numberToDirection(int number) const;
    int cordinateToLatitude(const std::string cordinate) const;
    int cordinateToLongitude(const std::string cordinate) const;
    void saveToFile(const std::string& filename) const;
    bool checkForColission() const;
    void changeBoardFieldState(BoardFieldState newState);
    bool placeShip(int latitude, int longitude, Direction direction, Ship ship);

    std::vector<Ship> shipsNextToBoard;
    std::vector<Ship> shipsOnBoard;
    BoardField grid[10][10]; //nicht 10 fest sondern irgendwie über die BoardSize
    char waterSymbol = '~';
    char shipSymbol = 'S';
    char shipPlaceSymbol = 'p';
     

private:
    void setupBoard();
    void setupShips();
    const int boardSize = 10;
    //Sammlung aller Spielfelder ungeordnet

    std::string gameID = "1";
    std::string playerID = "1";
    char splitSymbol = ';';
    

};
#endif