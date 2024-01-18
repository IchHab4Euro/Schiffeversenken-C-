#include "../include/ComputerBoard.h"

#include <iostream>
#include <random>
#include <vector>

void ComputerBoard::placeShips() {
    while(!shipsNextToBoard.empty()){
        Ship* shipToPlace = shipsNextToBoard.front();
        shipsNextToBoard.erase(shipsNextToBoard.begin());
        
        bool shipPlaced = false; 
        while(!shipPlaced){
            int startFieldLat = getRandomNumber(0,9);
            int startFieldLong = getRandomNumber(0,9);
            int directionNumber = getRandomNumber(0,3);
            Direction direction = numberToDirection(directionNumber);

            std::cout << "lat: " << startFieldLat << "long: " << startFieldLong << "direction Number: " << directionNumber << std::endl;
            
            shipPlaced = placeShip(startFieldLat, startFieldLong, direction, shipToPlace);
        }
        shipsOnBoard.push_back(shipToPlace);
    }
}

void ComputerBoard::attack(Board* board) {
    if(!firstHit || shipHit->isSunken()){
        firstHit = false;
        secondHit = false;
        BoardSegment* boardSegmentToHit;
        do{
            lastHitLat = getRandomNumber(0,boardSize - 1);
            lastHitLon = getRandomNumber(0,boardSize - 1);
            boardSegmentToHit = board->grid[lastHitLat][lastHitLon];
        } while(boardSegmentToHit->isWaterHit() || boardSegmentToHit->isShipHit() || boardSegmentToHit->isRevealed());

        if(boardSegmentToHit->isWater()) {
            boardSegmentToHit->setWaterHit();
        }
        if(boardSegmentToHit->isShip()) {
            boardSegmentToHit->setShipHit();
            shipHit = boardSegmentToHit->getShipOnSegment();
            neighboursRevealMode = 2;
            revealNeighbors(board, lastHitLat, lastHitLon, neighboursRevealMode);
            firstHit = true;
        }
    }
    else if(firstHit && !secondHit) {
        bool validDirectionFound = false;

        while (!validDirectionFound) {
            int revealDirection = getRandomNumber(0, 3); 

            switch (revealDirection) { 
                case 0: // North
                    latOffsetReveal = -1;
                    neighboursRevealMode = 1;
                    break;
                case 1: // East
                    lonOffsetReveal = 1;
                    neighboursRevealMode = 0;
                    break;
                case 2: // South
                    latOffsetReveal = 1;
                    neighboursRevealMode = 1;
                    break;
                case 3: // West
                    lonOffsetReveal = -1;
                    neighboursRevealMode = 0;
                    break;
                default:
                    break;
            }

            int newLat = lastHitLat + latOffsetReveal;
            int newLon = lastHitLon + lonOffsetReveal;

            if (newLat >= 0 && newLat < boardSize && newLon >= 0 && newLon < boardSize) {
                BoardSegment* boardSegmentToReveal = board->grid[newLat][newLon];

                if (boardSegmentToReveal->isWater()) {
                    boardSegmentToReveal->setWaterHit();
                    validDirectionFound = true;

                if (boardSegmentToReveal->isShip()) {
                    boardSegmentToReveal->setShipHit();
                    lastHitLat = newLat;
                    lastHitLon = newLon;
                    revealNeighbors(board, lastHitLat, lastHitLon, neighboursRevealMode);
                    secondHit = true;
                    validDirectionFound = true;
                    }
                }
            }
        }
    }
    else if (!(shipHit->isSunken())) {
        int lastHitLat = lastHitLat + latOffsetReveal;
        int lastHitLon = lastHitLon + lonOffsetReveal;
        board->grid[lastHitLat][lastHitLon]->setShipHit();
        revealNeighbors(board, lastHitLat, lastHitLon, neighboursRevealMode);
    }
}

void ComputerBoard::revealNeighbors(Board* boardToReveal, int latSegmentToCheck, int lonSegmentToCheck, int revealMode) {
    const int verticalOffsets[] = {-1, 1};
    const int horizontalOffsets[] = {-1, 1};

    switch (revealMode) {
        case 0: // North + South ;above + below 
            for (int latOffset : verticalOffsets) {
                int newLat = latSegmentToCheck + latOffset;

                if (newLat >= 0 && newLat < boardSize) {
                    BoardSegment* boardSegmentToReveal = boardToReveal->grid[newLat][lonSegmentToCheck];
                    if (boardSegmentToReveal->isWater()) {
                        boardSegmentToReveal->setRevealed();
                    }
                }
            }
            break;

        case 1: // West + East; left + right
            for (int lonOffset : horizontalOffsets) {
                int newLon = lonSegmentToCheck + lonOffset;

                if (newLon >= 0 && newLon < boardSize) {
                    BoardSegment* boardSegmentToReveal = boardToReveal->grid[latSegmentToCheck][newLon];
                    if (boardSegmentToReveal->isWater()) {
                        boardSegmentToReveal->setRevealed();
                    }
                }
            }
            break;

        case 2: // North-East + Soth-East + Soth-West + North-West; diagonal
            for (int latOffset : verticalOffsets) {
                for (int lonOffset : horizontalOffsets) {
                    int newLat = latSegmentToCheck + latOffset;
                    int newLon = lonSegmentToCheck + lonOffset;

                    if (newLat >= 0 && newLat < boardSize && newLon >= 0 && newLon < boardSize) {
                        BoardSegment* boardSegmentToReveal = boardToReveal->grid[newLat][newLon];
                        if (boardSegmentToReveal->isWater()) {
                            boardSegmentToReveal->setRevealed();
                        }
                    }
                }
            }
            break;

        default:
            // Ungültiger revealMode ---> Fehlerbehandlung!!!
            break;
    }
}

int ComputerBoard::getRandomNumber(int lowerBound, int upperBound){
    std::random_device randomNummerGen;
    std::mt19937 gen(randomNummerGen());
    std::uniform_int_distribution<int> distrubution(lowerBound,upperBound);

    return distrubution(gen);
}


