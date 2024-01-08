#include "Headerdateien/PlayerBoard.h"
#include "Headerdateien/Ship.h"

#include <iostream>
#include <vector>
#include <algorithm>

void PlayerBoard::placeShips() {
    while (!shipsNextToBoard.empty()) {
        std::cout << "Folgende Schiffe können platziert werden:" << std::endl;
        for (const Ship& ship : shipsNextToBoard) {
            std::cout << ship.getId() << " Name: " << ship.getName() << ", Länge: " << ship.getLength() << std::endl;
        }

        int pickedShipId = 0;
        while(!checkContainsShip(shipsNextToBoard,pickedShipId)){
            std::cout <<"Welches Schiff willst du platziere? (gebe eine gueltige Schiffs Id ein)" << std::endl;
            std::cin >> pickedShipId; //was wenn String angeben
        }

        Ship pickedShip = getShipById(shipsNextToBoard, pickedShipId);
        std::string shipCoordinates;
        int longitude, latitude, direction;

        bool shipPlaced = false; 
        while (!shipPlaced) {
            std::cout << "Du hast das Schiff: " << pickedShip.getName() << " mit einer Größe: " << pickedShip.getLength() << std::endl;
            std::cout << "Wohin soll das Schiff platziert werden? (Gib die Koordinaten an)" << std::endl;
            std::cin >> shipCoordinates;
            latitude = cordinateToLatitude(shipCoordinates);
            longitude = cordinateToLongitude(shipCoordinates);

            std::cout << "Bitte gib eine Richtung an, in der das Schiff platziert werden soll." << std::endl;
            std::cout << "0: unten, 1: oben, 2: rechts, 3: links" << std::endl;
            std::cin >> direction;

            shipPlaced = placeShip(latitude, longitude, direction, pickedShip);
        }

        /*
        bool shipPlaced = false;
        int direction; 
        while (!shipPlaced) {
            std::cout << "Bitte gib eine Richtung an, in der das Schiff platziert werden soll." << std::endl;
            std::cout << "0: unten, 1: oben, 2: rechts, 3: links" << std::endl;
            std::cin >> direction;
            shipPlaced = placeShip(latitude, longitude, direction, pickedShip);
        }
        */


        // Entferne das platzierte Schiff aus shipsNextToBoard
        shipsNextToBoard.erase(std::remove_if(shipsNextToBoard.begin(), shipsNextToBoard.end(), 
                                              [&pickedShip](const Ship& ship) { return ship.getId() == pickedShip.getId(); }), 
                               shipsNextToBoard.end());

        shipsOnBoard.push_back(pickedShip);
    }
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
