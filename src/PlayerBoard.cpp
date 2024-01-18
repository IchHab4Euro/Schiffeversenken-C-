#include "../include/PlayerBoard.h"

#include <iostream>
#include <vector>
#include <algorithm>

void PlayerBoard::placeShips() {
    int ships = shipsNextToBoard.size();
    while (!shipsNextToBoard.empty()) {

        Ship* selectedShip = shipSelection(ships);

        std::string shipCoordinates;
        std::string message;
        int longitude, latitude, directionNumber;
        bool shipPlaced = false;  
        while (!shipPlaced) {
            message = "Du hast das Schiff: " + selectedShip->getName() + " mit einer Gr\224sse: " + std::to_string(selectedShip->getLength());
            Output::printBoxMessage(message, true);
            shipCoordinates = Input::userinputCoordinates("Wohin soll das Schiff platziert werden? Gib die Koordinate ein: ", Board::getBoardSize());
            latitude = cordinateToLatitude(shipCoordinates);
            longitude = cordinateToLongitude(shipCoordinates);
            
            Output::printBoxMessage("Bitte gib eine Richtung an, in der das Schiff platziert werden soll.", true);
            std::vector<std::string> directions = {"North", "East", "South", "West"};
            Output::printMenue(directions);
            
            directionNumber = Input::userinputInt("W\204hlen sie eine Richtung: ", 1, 4);
 
            Direction direction = numberToDirection(directionNumber);

            shipPlaced = placeShip(latitude, longitude, direction, selectedShip);
            std::cout << shipPlaced << std::endl;
        }

        shipsNextToBoard.erase(std::remove_if(shipsNextToBoard.begin(), shipsNextToBoard.end(), 
                                      [&selectedShip](const Ship* ship) { return ship->getId() == selectedShip->getId(); }), 
                       shipsNextToBoard.end());

        shipsOnBoard.push_back(selectedShip);
    }
}

Ship* PlayerBoard::shipSelection(int ships)  {
    Output::printBoardWithMenue(this, shipsNextToBoard);
    std::string message = "Welches Schiff willst du platzieren?";
    int pickedShipId = 0;
    while(!checkContainsShip(shipsNextToBoard,pickedShipId)){
        pickedShipId = Input::userinputInt(message, 1, ships);
        if (!checkContainsShip(shipsNextToBoard, pickedShipId))  {
            message = "Sie haben dieses Schiff bereits platziert! Wählen sie ein neues";
        }  
    }
    return getShipById(shipsNextToBoard, pickedShipId);
}

bool PlayerBoard::checkContainsShip(std::vector<Ship*> shipList, int idToCheck) {
    for(const Ship* ship : shipList) {
        if(ship->getId() == idToCheck){
            return true;
        }
    }
    return false;
}

Ship* PlayerBoard::getShipById(std::vector<Ship*> shipList, int shipId) {
    for(Ship* ship : shipList) {
        if(ship->getId() == shipId) {
            return ship; //alternative als diese Methode was wenn if nicht zutrifft was wir returnt
        }
    }
    return nullptr;
}