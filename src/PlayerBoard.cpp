#include "../include/PlayerBoard.h"

#include <iostream>
#include <vector>
#include <algorithm>

/*
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
            message = "Sie haben dieses Schiff bereits platziert! Waehlen sie ein neues";
        }  
    }
    return getShipById(shipsNextToBoard, pickedShipId);
}*/

void PlayerBoard::placeShips() {
    std::string message; 
    while (true) {
        int shipsCount = shipsNextToBoard.size();
        if (shipsCount == 0) {
            Output::printBoxMessage("Alle Schiffe wurden platziert.", true);
            break;
        }

        Ship* selectedShip = shipSelection(shipsCount);
        if (!selectedShip) {//if shipSelection is 0;true -> shipDeletet or FieldResetet
            continue;
        }

        bool shipPlaced = false;
        while (!shipPlaced) {
             message = "Du hast das Schiff: " + selectedShip->getName() + 
                                  " mit einer Größe: " + std::to_string(selectedShip->getLength());
            Output::printBoxMessage(message, true);

            std::string shipCoordinates = Input::userinputCoordinates("Wohin soll das Schiff platziert werden? Gib die Koordinate ein: ", getBoardSize());
            int latitude = cordinateToLatitude(shipCoordinates);
            int longitude = cordinateToLongitude(shipCoordinates);

            Output::printBoxMessage("Bitte gib eine Richtung an, in der das Schiff platziert werden soll.", true);
            std::vector<std::string> directions = {"North", "East", "South", "West"};
            Output::printMenue(directions);

            int directionNumber = Input::userinputInt("Wähle eine Richtung: ", 1, 4);
            Direction direction = numberToDirection(directionNumber);

            shipPlaced = placeShip(latitude, longitude, direction, selectedShip);
            if (!shipPlaced) {
                Output::printBoxMessage("Alle Schiffe wurden platziert.", true);
            }
        }

        shipsNextToBoard.erase(std::remove_if(shipsNextToBoard.begin(), shipsNextToBoard.end(), 
                                      [&selectedShip](const Ship* ship) { return ship->getId() == selectedShip->getId(); }), 
                       shipsNextToBoard.end());
        shipsOnBoard.push_back(selectedShip);
    }
}

Ship* PlayerBoard::shipSelection(int ships) {
    Output::printBoardWithMenue(this, shipsNextToBoard);
    std::string message = "Welches Schiff willst du platzieren? (0 für Optionen)";
    Output::printBoxMessage(message, true);
    
    int pickedShipId = Input::userinputInt("Deine Wahl: ", 0, ships);

    if (pickedShipId == 0) {
        return handleShipPlacementOptions();
    }

    return getShipById(shipsNextToBoard, pickedShipId);
}

Ship* PlayerBoard::handleShipPlacementOptions() {
    std::vector<std::string> menueMessage = {"Schiff entfernen" , "Neustart"};
    Output::printMenue(menueMessage);
    int choice = Input::userinputInt("Wähle eine Option: ", 1, menueMessage.size());

    switch (choice) {
        case 1:
            removeShipProcedure();
            break;
        case 2:
            resetBoardPlacement();
            break;
    }
    return nullptr;
}

void PlayerBoard::removeShipProcedure() {
    int shipIdToRemove = Input::userinputInt("ID des zu entfernenden Schiffs: ", 1, shipsOnBoard.size());
    removeShip(getShipById(shipsOnBoard, shipIdToRemove));
}

void PlayerBoard::resetBoardPlacement() {

    for (int i = 0; i < boardSize; i++) { //ressetting every BoardSegment to Water.
        for (int j = 0; j < boardSize; j++) {
            grid[i][j]->setShipOnSegment(nullptr);
            grid[i][j]->fieldState = SegmentState::Water;
        }
    }
}
    

void PlayerBoard::removeShip(Ship* shipToRemove) {
    if (shipToRemove == nullptr) {
        Output::printBoxError ("Das Schiff existiert nicht!", true); 
        return;
    }

    for (int i = 0; i < boardSize; i++) { //reset all segments with the ship
        for (int j = 0; j < boardSize; j++) {
            if (grid[i][j]->getShipOnSegment() == shipToRemove) {
                grid[i][j]->setShipOnSegment(nullptr);
                grid[i][j]->fieldState = SegmentState::Water;
            }
        }
    }

    // Delete Ship from the OnBoardList
    shipsOnBoard.erase(std::remove(shipsOnBoard.begin(), shipsOnBoard.end(), shipToRemove), shipsOnBoard.end());
    std::cout << "Schiff " << shipToRemove->getName() << " wurde entfernt." << std::endl;
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


void PlayerBoard::attack(Board* enemyBoard) {
    std::string message;
    std::string attackCoordinates;

    message = "Gib die Koordinaten fuer deinen Angriff ein: ";
    Output::printBoxMessage(message, true);
    attackCoordinates = Input::userinputCoordinates("Gib die Koordinate ein: ", Board::getBoardSize());

    int latitude = cordinateToLatitude(attackCoordinates);
    int longitude = cordinateToLongitude(attackCoordinates);

    BoardSegment* targetSegment = enemyBoard->grid[latitude][longitude];

    if (targetSegment->isShip()) {
        targetSegment->setShipHit();

        message = "Treffer bei " + attackCoordinates + "!";
        Output::printBoxMessage(message, true);

        Ship* hitShip = targetSegment->getShipOnSegment();
        enemyBoard->setSunkenShips();
        if (hitShip->isSunken()) {
            message = "Du hast das Schiff " + hitShip->getName() + " versenkt!";
            Output::printBoxMessage(message, true);
        }
    } else if (targetSegment->isWater()) {
        targetSegment->setWaterHit();
        message = "Nur Wasser getroffen bei: " + attackCoordinates + ".";
        Output::printBoxMessage(message, true);
    } else {
        message = "Dieses Feld hast du bereits angegriffen!";
        Output::printBoxMessage(message, true);
    }
}

