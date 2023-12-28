#include "Headerdateien/ComputerBoard.h"
#include "Headerdateien/Ship.h"

#include <iostream>
#include <random>

void ComputerBoard::placeShips() {
    while(!shipsNextToBoard.empty()){
        Ship shipToPlace = shipsNextToBoard.back();
        shipsNextToBoard.pop_back();
        bool shipPlaced = false; 

        while(!shipPlaced){
            int startFieldLat = getRandomNumber(0,9);
            int startFieldLong = getRandomNumber(0,9);
            int direction= getRandomNumber(0,1);

            shipPlaced = placeShip(startFieldLat, startFieldLong, direction, shipToPlace);
        }
        shipsOnBoard.push_back(shipToPlace);

        printBoard();
    }
}

bool ComputerBoard::placeShip(int latitude, int longitude, int direction, Ship ship) {
    if(!direction){
        if(latitude + ship.getLength() > boardSize - 1){
            return false;
        }
        for(int i = 0; i < ship.getLength(); i++){
            if(grid[latitude + i][longitude] == waterSymbol){
                grid[latitude + i][longitude] = shipPlaceSymbol;
            }
        }
    }
     if(direction){
        if(longitude + ship.getLength() > boardSize - 1){
            return false;
        }
        for(int i = 0; i < ship.getLength(); i++){
            if(grid[latitude][longitude + i] == waterSymbol){
                grid[latitude][longitude + i] = shipPlaceSymbol;
            }
        }
    }

    if(checkForColission()){
        replacShipPlaceSymbol(waterSymbol);
        return false;
    }
    else{
        replacShipPlaceSymbol(shipSymbol);
    }
    return true;
}

int ComputerBoard::getRandomNumber(int lowerBound, int upperBound){
    std::random_device randomNummerGen;
    std::mt19937 gen(randomNummerGen());
    std::uniform_int_distribution<int> distrubution(lowerBound,upperBound);

    return distrubution(gen);
}