#include "../include/ComputerBoard.h"

#include <iostream>
#include <random>
#include <vector>

void ComputerBoard::placeShips() {
    while(!shipsNextToBoard.empty()){
        Ship* shipToPlace = shipsNextToBoard.front();
        shipsNextToBoard.erase(shipsNextToBoard.begin());
        std::cout << shipToPlace->getName() << std::endl;

        bool shipPlaced = false; 
        while(!shipPlaced){
            int startFieldLat = getRandomNumberWindows(0,9);
            int startFieldLong = getRandomNumberWindows(0,9);
            int directionNumber = getRandomNumberWindows(1,4);
            Direction direction = numberToDirection(directionNumber);

            shipPlaced = placeShip(startFieldLat, startFieldLong, direction, shipToPlace);
        }
        shipsOnBoard.push_back(shipToPlace);
    }
}

void ComputerBoard::attack(Board* board) {
    if (!firstHit || (shipHit != nullptr && shipHit->isSunken())) {
        // Debug-Ausgabe
        std::cout << "Entering initial attack phase..." << std::endl;

        BoardSegment* boardSegmentToHit;
        do {
            lastHitLat = getRandomNumber(0, boardSize - 1);
            lastHitLon = getRandomNumber(0, boardSize - 1);
            boardSegmentToHit = board->grid[lastHitLat][lastHitLon];
        } while (boardSegmentToHit->isWaterHit() || boardSegmentToHit->isShipHit() || boardSegmentToHit->isRevealed());

        if (boardSegmentToHit->isWater()) {
            boardSegmentToHit->setWaterHit();
            // Debug-Ausgabe
            std::cout << "Hit water at (" << lastHitLat << ", " << lastHitLon << ")" << std::endl;
        }
        if (boardSegmentToHit->isShip()) {
            boardSegmentToHit->setShipHit();
            shipHit = boardSegmentToHit->getShipOnSegment();
            neighboursRevealMode = 2;
            revealNeighbors(board, lastHitLat, lastHitLon, neighboursRevealMode);
            firstHit = true;
            // Debug-Ausgabe
            std::cout << "Hit ship at (" << lastHitLat << ", " << lastHitLon << ")" << std::endl;
        }
    }
    else if (firstHit && !secondHit) {
        // Debug-Ausgabe
        std::cout << "Entering second hit phase..." << std::endl;

        bool validDirectionFound = false;

        while (!validDirectionFound) {
            int revealDirection = getRandomNumber(1, 4);

            switch (revealDirection) {
                case 1: // North
                    latOffsetReveal = -1;
                    neighboursRevealMode = 1;
                    break;
                case 2: // East
                    lonOffsetReveal = 1;
                    neighboursRevealMode = 0;
                    break;
                case 3: // South
                    latOffsetReveal = 1;
                    neighboursRevealMode = 1;
                    break;
                case 4: // West
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
                    // Debug-Ausgabe
                    std::cout << "Hit water at (" << newLat << ", " << newLon << ")" << std::endl;
                }
                if (boardSegmentToReveal->isShip()) {
                    // Debug-Ausgabe
                    std::cout << "Trying to hit Ship at (" << newLat << ", " << newLon << ")" << std::endl;
                    boardSegmentToReveal->setShipHit();
                    lastHitLat = newLat;
                    lastHitLon = newLon;
                    revealNeighbors(board, lastHitLat, lastHitLon, neighboursRevealMode);
                    secondHit = true;
                    validDirectionFound = true;
                    board->setSunkenShips();
                    // Debug-Ausgabe
                    std::cout << "Hit ship at (" << newLat << ", " << newLon << ")" << std::endl;
                }
            }
        }
    }
    else if (shipHit != nullptr && !shipHit->isSunken()) {
        // Debug-Ausgabe
        std::cout << "Continuing to attack previously hit ship..." << std::endl;

        int newLat = lastHitLat + latOffsetReveal;
        int newLon = lastHitLon + lonOffsetReveal;
        board->grid[newLat][newLon]->setShipHit();
        revealNeighbors(board, newLat, newLon, neighboursRevealMode);
        board->setSunkenShips();
        // Debug-Ausgabe
        std::cout << "Continuing attack on ship at (" << newLat << ", " << newLon << ")" << std::endl;
    }

    if (shipHit != nullptr && shipHit->isSunken()) {
        shipHit = nullptr;
        firstHit = false;
        secondHit = false;
        // Debug-Ausgabe
        std::cout << "Resetting attack state after sinking a ship." << std::endl;
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

int ComputerBoard::getRandomNumberWindows(int lowerBound, int upperBound)  {
    std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));
    std::uniform_int_distribution<> distribut(lowerBound, upperBound);
    return distribut(gen);
}

