#include "../include/Board.h"

#include <iostream>
#include <fstream>

Board::Board(){
}


void Board::init(std::vector<Ship*> ships) {
    //setup grid
    for(int lat = 0; lat < boardSize; lat++){
        for(int lon = 0; lon < boardSize; lon++){
            grid[lat][lon] = new BoardSegment(BoardSegment::FieldState::Water);
        }
    }
    shipsNextToBoard = ships;
}

int Board::getBoardSize() {
    return this->boardSize;
}


bool Board::placeShip(int latitude, int longitude, Direction direction, Ship* ship) {
    std::vector<BoardSegment*> segmentsOfShip;
    BoardSegment* BoardSegmentToPlace;
    std::string testDirection = "test"; 
    switch (direction)
    {
        case Direction::North://up, North
            if(latitude - ship->getLength() < 0){
                return false;
            }
            for(int i = 0; i < ship->getLength(); i++){
                BoardSegmentToPlace = grid[latitude - i][longitude];
                if(BoardSegmentToPlace->isWater()){
                    BoardSegmentToPlace->fieldState = BoardSegment::FieldState::ShipPlacement;
                    segmentsOfShip.push_back(BoardSegmentToPlace);
                }
                else {
                    replaceShipPlacement(BoardSegment::FieldState::Water);
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
                    BoardSegmentToPlace->fieldState = BoardSegment::FieldState::ShipPlacement;
                    segmentsOfShip.push_back(BoardSegmentToPlace);
                }
                else {
                    replaceShipPlacement(BoardSegment::FieldState::Water);
                    return false;
                }
            }
            testDirection = "Süden";
        break;

        case Direction::East://left, East
            if(longitude - ship->getLength() < 0){
                return false;
            }
            for(int i = 0; i < ship->getLength(); i++){
                BoardSegmentToPlace = grid[latitude][longitude - i];
                if(BoardSegmentToPlace->isWater()){
                    BoardSegmentToPlace->fieldState = BoardSegment::FieldState::ShipPlacement;
                    segmentsOfShip.push_back(BoardSegmentToPlace);
                }
                else {
                    replaceShipPlacement(BoardSegment::FieldState::Water);
                    return false;
                }
                
            }
            testDirection = "Osten";
        break;

        case Direction::West://right, West
            if(longitude + ship->getLength() > boardSize){
                return false;
            }
            for(int i = 0; i < ship->getLength(); i++){
                BoardSegmentToPlace = grid[latitude][longitude + i];
                if(BoardSegmentToPlace->isWater()){
                    BoardSegmentToPlace->fieldState = BoardSegment::FieldState::ShipPlacement;
                    segmentsOfShip.push_back(BoardSegmentToPlace);
                }
                else {
                    replaceShipPlacement(BoardSegment::FieldState::Water);
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
        replaceShipPlacement(BoardSegment::FieldState::Ship);
        return true; 
    }
    else {
        std::cout<<"Es kommt zu Kollision!";
        replaceShipPlacement(BoardSegment::FieldState::Water);
        return false;
    }
}

bool Board::checkForColission() const{
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            if(grid[i][j]->fieldState == BoardSegment::FieldState::ShipPlacement){
                if(grid[i - 1][j]->fieldState == BoardSegment::FieldState::Ship || //collision North
                grid[i + 1][j]->fieldState == BoardSegment::FieldState::Ship || //collision South
                grid[i][j - 1]->fieldState == BoardSegment::FieldState::Ship || //collision East
                grid[i][j + 1]->fieldState == BoardSegment::FieldState::Ship || //collision West
                grid[i - 1][j - 1]->fieldState == BoardSegment::FieldState::Ship || //collision North-East
                grid[i - 1][j + 1]->fieldState == BoardSegment::FieldState::Ship || //collision North-West
                grid[i + 1][j - 1]->fieldState == BoardSegment::FieldState::Ship || //collision South-East
                grid[i + 1][j + 1]->fieldState == BoardSegment::FieldState::Ship    //collision South-West
                )
                return true;
            }
        }
    }
    return false; 
}

void Board::replaceShipPlacement(BoardSegment::FieldState newState) {
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            if(grid[i][j]->fieldState == BoardSegment::FieldState::ShipPlacement){
                grid[i][j]->fieldState = newState;
            }
        }
    }
}

int Board::cordinateToLatitude(const std::string cordinate) const {
    if (cordinate.length() == 2){
        int latitude = cordinate[0] - 'A';
        return latitude;
    }
    return 0;
}

int Board::cordinateToLongitude(const std::string cordinate) const {
    if (cordinate.length() == 2){
        int longitude = cordinate[1] - '1';
        return longitude;
    }
    return 0;
}

Direction Board::numberToDirection(int number)  const { 
    switch (number) {
        case 0:
            return Direction::North;
        case 1:
            return Direction::East;
        case 2:
            return Direction::South;
        case 3:
            return Direction::East;
        default:
            throw std::invalid_argument("Invalid number for Direction"); //exc. Klasse erstellen und exc. abfangen und verarbeiten 
    }
}

