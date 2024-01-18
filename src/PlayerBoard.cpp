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
            message = "Du hast das Schiff: " + selectedShip->getName() + " mit einer Gr\224sse: " + std::to_string(selectedShip->getLength()) + ". Wohin soll das Schiff platziert werden?";
            Output::printBoxMessage(message);
            shipCoordinates = Input::userinputCoordinates("Gib die Koordinate ein: ", Board::getBoardSize());
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

Ship* PlayerBoard::shipSelection(){ //Todo: Output::shipSelection(ships)
    std::cout << "Folgende Schiffe k\224nnen platziert werden:" << std::endl;
        for (const Ship* ship : shipsNextToBoard) {
            std::cout << ship->getId() << " Name: " << ship->getName() << ", L\204nge: " << ship->getLength() << std::endl;
        }
        int pickedShipId = 0;
        //Todo: Input::shipSelection(ships)
        while(!checkContainsShip(shipsNextToBoard,pickedShipId)){
            std::cout <<"Welches Schiff willst du platziere? (gebe eine g\201ltige Schiffs Id ein)" << std::endl;
            std::cin >> pickedShipId; //was wenn String angeben
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
