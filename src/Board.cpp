#include "../include/Board.h"

#include <iostream>
#include <fstream>

Board::Board(){
}

//Nicht fertig
void Board::init(BoardSegment* initGrid, std::vector<Ship*> initShips) {
    //setup grid

    if (initGrid == nullptr)  {
        for(int lat = 0; lat < boardSize; lat++){
        for(int lon = 0; lon < boardSize; lon++){
            initGrid[lat][lon] = new BoardSegment(SegmentState::Water);
        }
    }    
    }
    shipsNextToBoard = initShips;
}

int Board::getBoardSize() {
    return this->boardSize;
}

bool Board::placeShip(int latitude, int longitude, Direction direction, Ship* ship) {
    BoardSegment* BoardSegmentToPlace;
    std::string testDirection = "test"; 
    switch (direction)
    {
        case Direction::North://up, North
            if(latitude - ship->getLength() < -1){
                return false;
            }
            for(int i = 0; i < ship->getLength(); i++){
                BoardSegmentToPlace = grid[latitude - i][longitude];
                if(BoardSegmentToPlace->isWater()){
                    BoardSegmentToPlace->fieldState = SegmentState::ShipPlacement;
                }
                else {
                    replaceShipPlacement(SegmentState::Water, nullptr);
                    return false;
                }
            }
            testDirection = "Norden";
        break;

        case Direction::South: //down, South
            if(latitude + ship->getLength() > boardSize){
                return false;
            }
            for(int i = 0; i < ship->getLength(); i++){
                BoardSegmentToPlace = grid[latitude + i][longitude];
                if(BoardSegmentToPlace->isWater()){
                    BoardSegmentToPlace->fieldState = SegmentState::ShipPlacement;
                }
                else {
                    replaceShipPlacement(SegmentState::Water, nullptr);
                    return false;
                }
            }
            testDirection = "Süden";
        break;

        case Direction::East://left, East
            if(longitude + ship->getLength() > boardSize){
                return false;
            }
            for(int i = 0; i < ship->getLength(); i++){
                BoardSegmentToPlace = grid[latitude][longitude + i];
                if(BoardSegmentToPlace->isWater()){
                    BoardSegmentToPlace->fieldState = SegmentState::ShipPlacement;
                }
                else {
                    replaceShipPlacement(SegmentState::Water, nullptr);
                    return false;
                }
            }
            testDirection = "Osten";
        break;

        case Direction::West://right, West
            if(longitude - ship->getLength() < -1){
                return false;
            }
            for(int i = 0; i < ship->getLength(); i++){
                BoardSegmentToPlace = grid[latitude][longitude - i];
                if(BoardSegmentToPlace->isWater()){
                    BoardSegmentToPlace->fieldState = SegmentState::ShipPlacement;
                }
                else {
                    replaceShipPlacement(SegmentState::Water, nullptr);
                    return false;
                }
            }
            testDirection = "Westen";
        break;

        default:
            std::cout<<"Falsche Eingabe Richtung";
            return false;
            break;
        }

    if (!(checkForColission())) {
        std::cout<<"Schiff konnte platziert werden lat " << latitude << " lon " << longitude << " Direction " << testDirection << std::endl;
        replaceShipPlacement(SegmentState::Ship, ship);
        return true; 
    }
    else {
        //std::cout<<"Es kommt zur Kollision!"<<std::endl;
        replaceShipPlacement(SegmentState::Water, nullptr);
        return false;
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
    for (Ship* ship : shipsOnBoard) {
        if (!ship->isSunken()) {
            bool allHits = true;

            // Überprüfe alle Segmente des Schiffes
            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    BoardSegment* segment = grid[i][j];

                    // Wenn das Segment zum Schiff gehört und nicht getroffen wurde
                    if (segment->getShipOnSegment() == ship && 
                        !(segment->isShipHit())) {
                        allHits = false;
                        break;
                    }
                }
                if (!allHits) break;
            }

            if (allHits) {
                ship->sunk = true;
            }
        }
    }
}

bool Board::allShipsSunk() const {
    bool allSunk = true;
    for (Ship* ship : shipsOnBoard) {
        if (!(ship->isSunken())) {
            allSunk = false;
        } else {
            std::cout << "Ship sunk: " << ship->getName() << std::endl;
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