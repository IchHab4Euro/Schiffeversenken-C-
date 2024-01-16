#include "../include/PlayerBoard.h"
#include "../include/Ship.h"

#include <iostream>
#include <vector>
#include <algorithm>

void PlayerBoard::placeShips() {
    while (!shipsNextToBoard.empty()) {

        Ship selectedShip = shipSelection();

        std::string shipCoordinates;
        int longitude, latitude, directionNumber;
        bool shipPlaced = false;  
        while (!shipPlaced) {
            //Todo: Output::shipLocation
            std::cout << "Du hast das Schiff: " << selectedShip.getName() << " mit einer Größe: " << selectedShip.getLength() << std::endl;
            std::cout << "Wohin soll das Schiff platziert werden? (Gib die Koordinaten an)" << std::endl;
            //Todo: Input::shipLocation
            std::cin >> shipCoordinates;
            latitude = cordinateToLatitude(shipCoordinates);
            longitude = cordinateToLongitude(shipCoordinates);
            
            //Todo: Output::shipDirecion
            std::cout << "Bitte gib eine Richtung an, in der das Schiff platziert werden soll." << std::endl;
            std::cout << "0: unten, 1: oben, 2: rechts, 3: links" << std::endl;
            //Todo: Input::shipDirecion
            std::cin >> directionNumber;

            Direction direction = numberToDirection(directionNumber);

            shipPlaced = placeShip(latitude, longitude, direction, selectedShip);
        }

        shipsNextToBoard.erase(std::remove_if(shipsNextToBoard.begin(), shipsNextToBoard.end(), 
                                              [&selectedShip](const Ship& ship) { return ship.getId() == selectedShip.getId(); }), 
                               shipsNextToBoard.end());

        shipsOnBoard.push_back(selectedShip);
    }
}

Ship PlayerBoard::shipSelection(){ //Todo: Output::shipSelection(ships)
    std::cout << "Folgende Schiffe können platziert werden:" << std::endl;
        for (const Ship& ship : shipsNextToBoard) {
            std::cout << ship.getId() << " Name: " << ship.getName() << ", Länge: " << ship.getLength() << std::endl;
        }
        int pickedShipId = 0;
        //Todo: Input::shipSelection(ships)
        while(!checkContainsShip(shipsNextToBoard,pickedShipId)){
            std::cout <<"Welches Schiff willst du platziere? (gebe eine gueltige Schiffs Id ein)" << std::endl;
            std::cin >> pickedShipId; //was wenn String angeben
        }
        return getShipById(shipsNextToBoard, pickedShipId);
}

bool PlayerBoard::checkContainsShip(std::vector<Ship> shipList, int idToCheck) {
    for(const Ship& ship : shipList) {
        if(ship.getId() == idToCheck){
            return true;
        }
    }
    return false;
}

Ship PlayerBoard::getShipById(std::vector<Ship> shipList, int shipId) {
    for(const Ship& ship : shipList) {
        if(ship.getId() == shipId) {
            return ship; //alternative als diese Methode was wenn if nicht zutrifft was wir returnt
        }
    }
}
