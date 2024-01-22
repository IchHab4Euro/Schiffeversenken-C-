#include "../include/Board.h"

#include <iostream>
#include <fstream>

Board::Board(){


}

void Board::init(std::vector<BoardSegment*> initSegments, std::vector<Ship*> initShips, bool gamePhase) {
    // Setup grid
    if (initSegments.empty()) {
        for (int lat = 0; lat < boardSize; lat++) {
            for (int lon = 0; lon < boardSize; lon++) {
                grid[lat][lon] = new BoardSegment(SegmentState::Water);
            }
        }
    }
    else {
        for (int lat = 0; lat < boardSize; lat++) {
            for (int lon = 0; lon < boardSize; lon++) {
                grid[lat][lon] = initSegments[lat * boardSize + lon];
            }
        }
    }

    if (gamePhase == true)  { //ships already placed
        shipsOnBoard = initShips;
    } else  {
        shipsNextToBoard = initShips;
        initShipsReset = initShips; //for resetting the whole board
    }
}

int Board::getBoardSize() {
    return this->boardSize;
}

bool Board::placeShip(int latitude, int longitude, Direction direction, Ship* ship) {
    if (!isValidPlacement(latitude, longitude, direction, ship)) {
        return false;
    }

    // Place Segments for the Ship
    for (int i = 0; i < ship->getLength(); i++) {
        BoardSegment* segmentToPlace = getSegmentToPlace(latitude, longitude, direction, i);
        segmentToPlace->fieldState = SegmentState::ShipPlacement;
    }

    // Check for collision after Segments are set 
    if (checkForColission()) {
        replaceShipPlacement(SegmentState::Water, nullptr); // Entfernt vorläufige Platzierung
        return false;
    }

    // Final Ship placement 
    replaceShipPlacement(SegmentState::Ship, ship);
    std::cout << "Schiff platziert: " << ship->getName() << std::endl;
    return true;
}

bool Board::isValidPlacement(int latitude, int longitude, Direction direction, Ship* ship) const {
    for (int i = 0; i < ship->getLength(); i++) {
        int latToCheck, lonToCheck;
        switch (direction) {
            case Direction::North:
                latToCheck = latitude - i;
                lonToCheck = longitude;
                break;
            case Direction::South:
                latToCheck = latitude + i;
                lonToCheck = longitude;
                break;
            case Direction::East:
                latToCheck = latitude;
                lonToCheck = longitude + i;
                break;
            case Direction::West:
                latToCheck = latitude;
                lonToCheck = longitude - i;
                break;
            default:
                return false;
        }

        // check grid Area
        if (latToCheck < 0 || latToCheck >= boardSize || lonToCheck < 0 || lonToCheck >= boardSize) {
            return false;
        }

        // Check for collision
        BoardSegment* segment = grid[latToCheck][lonToCheck];
        if (segment->isShip() || segment->isShipPlacement()) {
            return false;
        }
    }
    return true;
}

BoardSegment* Board::getSegmentToPlace(int latitude, int longitude, Direction direction, int offset) const {
    int latToPlace, lonToPlace;
    switch (direction) {
        case Direction::North:
            latToPlace = latitude - offset;
            lonToPlace = longitude;
            break;
        case Direction::South:
            latToPlace = latitude + offset;
            lonToPlace = longitude;
            break;
        case Direction::East:
            latToPlace = latitude;
            lonToPlace = longitude + offset;
            break;
        case Direction::West:
            latToPlace = latitude;
            lonToPlace = longitude - offset;
            break;
        default:
            throw std::invalid_argument("Ungültige Richtung für die Platzierung des Schiffs");
    }

    return grid[latToPlace][lonToPlace];
}

void Board::replaceShipPlacement(SegmentState newState, Ship* shipToPlace) {
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            if(grid[i][j]->fieldState == SegmentState::ShipPlacement){
                grid[i][j]->fieldState = newState;
                grid[i][j]->setShipOnSegment(shipToPlace);
            }
        }
    }
}

bool Board::checkForColission() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (grid[i][j]->fieldState == SegmentState::ShipPlacement) {
                if ((i > 0 && grid[i - 1][j]->fieldState == SegmentState::Ship) || //collision North
                    (i < boardSize - 1 && grid[i + 1][j]->fieldState == SegmentState::Ship) || //collision South
                    (j > 0 && grid[i][j - 1]->fieldState == SegmentState::Ship) || //collision East
                    (j < boardSize - 1 && grid[i][j + 1]->fieldState == SegmentState::Ship) || //collision West
                    (i > 0 && j > 0 && grid[i - 1][j - 1]->fieldState == SegmentState::Ship) || //collision North-East
                    (i > 0 && j < boardSize - 1 && grid[i - 1][j + 1]->fieldState == SegmentState::Ship) || //collision North-West
                    (i < boardSize - 1 && j > 0 && grid[i + 1][j - 1]->fieldState == SegmentState::Ship) || //collision South-East
                    (i < boardSize - 1 && j < boardSize - 1 && grid[i + 1][j + 1]->fieldState == SegmentState::Ship) //collision South-West
                ) {
                    return true;
                }
            }
        }
    }
    return false;
}

int Board::cordinateToLatitude(const std::string cordinate) const {
    int latitude = cordinate[0] - 'A';
    return latitude;
}

int Board::cordinateToLongitude(const std::string cordinate) const {
    int longitude = 0;
    for (size_t i = 1; i < cordinate.size(); i++) {
        longitude = longitude * 10 + (cordinate[i] - '0');
    }
    return longitude - 1;
}

Direction Board::numberToDirection(int number)  const { 
    switch (number) {
        case 1:
            return Direction::North;
        case 2:
            return Direction::East;
        case 3:
            return Direction::South;
        case 4:
            return Direction::West;
        default:
            throw std::invalid_argument("Invalid number for Direction"); //exc. Klasse erstellen und exc. abfangen und verarbeiten 
    }
}


void Board::setSunkenShips() {
    for(int i = 0; i < boardSize; i++) {
        for(int j = 0; j < boardSize; j++) {
            BoardSegment* segmentToCheck = grid[i][j];

            if(segmentToCheck->isShipHit()){
                bool shipSunken = true;
                Ship* shipToCheck = segmentToCheck->getShipOnSegment();
                for(int h = 0; h < boardSize; h++) {
                    for(int k = 0; k < boardSize; k++) {
                        BoardSegment* segmentToCheckOfShip = grid[h][k];
                        if(segmentToCheckOfShip->getShipOnSegment() != nullptr){
                            if(segmentToCheckOfShip->getShipOnSegment() == shipToCheck && !(segmentToCheckOfShip->isShipHit())) {
                                shipSunken = false;
                            }
                        }
                    }
                }
                if(shipSunken){
                    shipToCheck->setSunken();
                }
            }   
        }
    }
}

bool Board::allShipsSunk() const {
    bool allSunk = true;
    for (int i = 0; i < shipsOnBoard.size(); i++) {
        Ship* shipToCheck = shipsOnBoard[i];
        if (!(shipToCheck->isSunken())) {
            allSunk = false;
        } else {
            std::cout << "Ship sunk: " << shipToCheck->getName() << std::endl;
        }
    }
    
    if (allSunk) {
        std::cout << "All ships have been sunk!" << std::endl;
    } else {
        std::cout << "Not all ships are sunk yet." << std::endl;
    }

    return allSunk;
}

std::vector<Ship*> Board::getShipsNextToBoard()  {
    return shipsNextToBoard;
}

std::vector<Ship*> Board::getShipsOnBoard() {
    return shipsOnBoard;
}

