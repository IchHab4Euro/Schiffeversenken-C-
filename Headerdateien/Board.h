#pragma once

#include "Ship.h"

#include <iostream>
#include <vector>

class Board {

public:
    Board();
    void printBoard() const;
    void saveToFile(const std::string& filename) const;
    int cordinateToLatitude(const std::string cordinate) const;
    int cordinateToLongitude(const std::string cordinate) const;
    bool checkForColission() const;
    void replacShipPlaceSymbol(char replacer);
    bool placeShip(int latitude, int longitude, int direction, Ship ship);

    virtual void placeShips() = 0;
    

protected:
    std::vector<Ship> shipsNextToBoard;
    std::vector<Ship> shipsOnBoard;
    char grid[10][10];
    char waterSymbol = '~';
    char shipSymbol = 's';
    char shipPlaceSymbol = 'p';
    const int boardSize = 10; 

private:
    std::string gameID = "1";
    std::string playerID = "1";
    char splitSymbol = ';';

};
