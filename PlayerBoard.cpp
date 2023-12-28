#include "Headerdateien/PlayerBoard.h"
#include "Headerdateien/Ship.h"

#include <iostream>

void PlayerBoard::placeShips() {
    std::cout <<"folgende Schiffe koennen platziert werden" << std::endl;

    for(const Ship& ship : shipsNextToBoard) {
        std::cout << "Name: " << ship.getName() << ", Laenge: " << ship.getLength() << std::endl;
    }

    std::cout <<"welches Schiff willst du platzieren?" << std::endl;

    

}