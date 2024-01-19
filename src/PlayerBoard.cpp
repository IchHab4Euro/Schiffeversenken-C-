#include "../include/PlayerBoard.h"

#include <iostream>
#include <vector>
#include <algorithm>

void PlayerBoard::placeShips() {
    while (!shipsNextToBoard.empty()) {

        Ship* selectedShip = shipSelection();

        std::string shipCoordinates;
        std::string message;
        int longitude, latitude, directionNumber;
        bool shipPlaced = false;  
        while (!shipPlaced) {
            message = "Du hast das Schiff: " + selectedShip->getName() + " mit einer Gr\224sse: " + std::to_string(selectedShip->getLength());
            Output::printBoxMessage(message);
            shipCoordinates = Input::userinputCoordinates("Wohin soll das Schiff platziert werden? Gibt die Koordinaten ein: ", Board::getBoardSize());
            latitude = cordinateToLatitude(shipCoordinates);
            longitude = cordinateToLongitude(shipCoordinates);
            
            Output::printBoxMessage("Bitte gib eine Richtung an, in der das Schiff platziert werden soll.");
            std::vector<std::string> directions = {"0: North", "1: East", "2: South", "3: West"};
            Output::printMenue(directions);
            
            directionNumber = Input::userinputInt("W\204hlen sie eine Richtung: ", 0, 3);
 
            Direction direction = numberToDirection(directionNumber);

            std::cout << std::to_string(latitude) << std::to_string(longitude) << std::to_string(directionNumber) << selectedShip->getName() << std::endl;
            shipPlaced = placeShip(latitude, longitude, direction, selectedShip);
            std::cout << shipPlaced << std::endl;
        }

        shipsNextToBoard.erase(std::remove_if(shipsNextToBoard.begin(), shipsNextToBoard.end(), 
                                      [&selectedShip](const Ship* ship) { return ship->getId() == selectedShip->getId(); }), 
                       shipsNextToBoard.end());

        shipsOnBoard.push_back(selectedShip);
    }
}

Ship* PlayerBoard::shipSelection()  {
    Output::printBoardWithMenue(this, shipsNextToBoard);
    std::string message = "Welches Schiff willst du platzieren?";
    int pickedShipId = 0;
    while(!checkContainsShip(shipsNextToBoard,pickedShipId)){
        pickedShipId = Input::userinputInt(message, 1, shipsNextToBoard.size());
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
