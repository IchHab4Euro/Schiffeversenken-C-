#include "Headerdateien/ComputerBoard.h"
#include "Headerdateien/Ship.h"

#include <iostream>
#include <random>
#include <vector>

void ComputerBoard::placeShips() {
    while(!shipsNextToBoard.empty()){
        Ship shipToPlace = shipsNextToBoard[0];
        shipsNextToBoard.erase(shipsNextToBoard.begin());
        bool shipPlaced = false; 

        while(!shipPlaced){
            int startFieldLat = getRandomNumber(0,9);
            int startFieldLong = getRandomNumber(0,9);
            int direction= getRandomNumber(0,3);

            shipPlaced = placeShip(startFieldLat, startFieldLong, direction, shipToPlace);
        }
        shipsOnBoard.push_back(shipToPlace);
    }
}

int ComputerBoard::getRandomNumber(int lowerBound, int upperBound){
    std::random_device randomNummerGen;
    std::mt19937 gen(randomNummerGen());
    std::uniform_int_distribution<int> distrubution(lowerBound,upperBound);

    return distrubution(gen);
}