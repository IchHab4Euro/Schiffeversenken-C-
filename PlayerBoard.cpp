#include "Headerdateien/PlayerBoard.h"
#include "Headerdateien/Ship.h"

#include <iostream>
#include <vector>
#include <algorithm>

void PlayerBoard::placeShips() {
    while(!shipsNextToBoard.empty()){
        std::cout <<"folgende Schiffe koennen platziert werden" << std::endl;

        for(const Ship& ship : shipsNextToBoard) {
            std::cout << ship.getId() << " Name: " << ship.getName() << ", Laenge: " << ship.getLength() << std::endl;
        }

        int pickedShipId = 0;
        
        while(!checkContainsShip(shipsNextToBoard,pickedShipId)){
            std::cout <<"Welches Schiff willst du platziere? (gebe eine gueltige Schiffs Id ein)" << std::endl;
            std::cin >> pickedShipId; //was wenn String angeben
        }

        Ship pickedShip = getShipById(shipsNextToBoard,pickedShipId);

        std::string shipCordinates;
        int latitude = boardSize;
        int longitude = boardSize;
        while(!(latitude >= 0 && latitude < boardSize && longitude >= 0 && longitude < boardSize) || shipCordinates.length() > 2){
            std::cout << "Du hast das Schiff: " << pickedShip.getName() << "Mit einer groesse: " << pickedShip.getLength() << std::endl;
            std::cout << "Wohin soll das Schiff plaziert werden (geben Sie die Koordianate an)" << std::endl;
            std::cin >> shipCordinates;
            latitude = cordinateToLatitude(shipCordinates);
            longitude = cordinateToLongitude(shipCordinates);
        }

        int direction = 5; //vorwert ist das nötig?
        while(direction < 0 || direction > 3){
            std::cout << "Bitte gebe eine Richtung an in der das Schiff plaziert werden soll." << std::endl;
            std::cout << "Das Schifft wird von deiner angebenen Koordinate in die Richtung aufgebaut die du waehlst." << std::endl;
            std::cout << "0: unten \n 1: oben \n 2: rechts \n 3: links" << std::endl;
            std::cin >> direction;
        }

        std::cout << "Lat: " << latitude << "Lon: " << longitude << std::endl;

        placeShip(latitude,longitude,direction,pickedShip);

        shipsNextToBoard.erase(std::remove(shipsNextToBoard.begin(), shipsNextToBoard.end(), pickedShip), shipsNextToBoard.end());
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

void deleteShipFromVector(std::vector<Ship>& shipVector, Ship toDelete) {
    for(std::vector<Ship>:: iterator it = shipVector.begin(); i != shipVector.end()
}
