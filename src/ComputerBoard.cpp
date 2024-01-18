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
            int startFieldLat = getRandomNumber(0,9);
            int startFieldLong = getRandomNumber(0,9);
            int directionNumber = getRandomNumber(1,4);
            Direction direction = numberToDirection(directionNumber);

            shipPlaced = placeShip(startFieldLat, startFieldLong, direction, shipToPlace);
        }
        shipsOnBoard.push_back(shipToPlace);
    }
}

void ComputerBoard::attack(Board* board) {
    if (!firstHit) {
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
            int revealDirection = getRandomNumber(1, 4);

            switch (revealDirection) {
                case 1: // North
                case 1: // North
                    latOffsetReveal = -1;
                    lonOffsetReveal = 0;
                    neighboursRevealMode = 1;
                    break;
                case 2: // East
                    latOffsetReveal = 0;
                    lonOffsetReveal = 1;
                    neighboursRevealMode = 0;
                    break;
                case 3: // South
                case 3: // South
                    latOffsetReveal = 1;
                    lonOffsetReveal = 0;
                    neighboursRevealMode = 1;
                    break;
                case 4: // West
                    latOffsetReveal = 0;
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
                std::cout << "Completet Check for number in grid newLat: " << newLat << "new Lon: " << newLon << std::endl;

                if (boardSegmentToReveal->isWater()) {
                    boardSegmentToReveal->setWaterHit();
                    validDirectionFound = true;
                    // Debug-Ausgabe
                    std::cout << "Hit water at (" << newLat << ", " << newLon << ")" << std::endl;
                }
                if (boardSegmentToReveal->isShip()) { //second Hit found right direction
                    // Debug-Ausgabe
                    std::cout << "Trying to hit Ship at (" << newLat << ", " << newLon << ")" << std::endl;
                    boardSegmentToReveal->setShipHit();
                    lastHitLat = newLat;
                    lastHitLon = newLon;
                    revealNeighbors(board, lastHitLat, lastHitLon, neighboursRevealMode);
                    secondHit = true;
                    moveCounter++;
                    validDirectionFound = true;
                    board->setSunkenShips();
                    // Debug-Ausgabe
                    std::cout << "Hit ship at (" << newLat << ", " << newLon << ")" << std::endl;
                }
            }
        }
    }
    else if (shipHit != nullptr && !shipHit->isSunken() && secondHit) {
        // Debug-Ausgabe
        std::cout << "Continuing to attack previously hit ship..." << std::endl;

        lastHitLat = lastHitLat + latOffsetReveal;
        lastHitLon = lastHitLon + lonOffsetReveal;
        BoardSegment* boardSegmentToHit  = board->grid[lastHitLat][lastHitLon];

        if(boardSegmentToHit->isShip()) { //Ship Hit 
            boardSegmentToHit->setShipHit();
            moveCounter++;
            revealNeighbors(board, lastHitLat, lastHitLon, neighboursRevealMode);
            board->setSunkenShips();
            // Debug-Ausgabe
            std::cout << "Continuing attack on ship at (" << lastHitLat << ", " << lastHitLon << ")" << std::endl;
            
        }
        else if(boardSegmentToHit->isWater()) {
            moveCounter++;
            boardSegmentToHit->setWaterHit();
            // Debug-Ausgabe
            std::cout << "Hit water at (" << lastHitLat << ", " << lastHitLon << ")" << std::endl;
            if(latOffsetReveal != 0) {
                latOffsetReveal = latOffsetReveal * (-1);
                lastHitLat = lastHitLat + (moveCounter * latOffsetReveal);  
            }
            if(lonOffsetReveal != 0) {
                lonOffsetReveal = lonOffsetReveal * (-1);
                lastHitLon = lastHitLon + (moveCounter * lonOffsetReveal);  
            }
            moveCounter = 0;
            // Debug-Ausgabe
            std::cout << "neuer lastHit nach Richtungswechsel wegen Wasser(" << lastHitLat << ", " << lastHitLon << ")" << std::endl;
            
        }
        else{
            if(latOffsetReveal != 0) {
                latOffsetReveal = latOffsetReveal * (-1);
                lastHitLat = lastHitLat + moveCounter * latOffsetReveal;  
            }
            if(lonOffsetReveal != 0) {
                lonOffsetReveal = lonOffsetReveal * (-1);
                lastHitLon = lastHitLon + moveCounter * lonOffsetReveal;  
            }
            moveCounter = 0;
            attack(board);
            // Debug-Ausgabe
            std::cout << "Changing attack direction due to obstacle." << std::endl;
        }
    }
    if (shipHit != nullptr && shipHit->isSunken()) {
        shipHit = nullptr;
        firstHit = false;
        secondHit = false;
        moveCounter = 0;
        // Debug-Ausgabe
        std::cout << "Resetting attack state after sinking a ship." << std::endl;
        exit(0);
    }
}

void ComputerBoard::revealNeighbors(Board* boardToReveal, int latSegmentToCheck, int lonSegmentToCheck, int revealMode) {
    const int verticalOffsets[] = {-1, 1};
    const int horizontalOffsets[] = {-1, 1};

    // Diagonalen immer aufdecken
    std::cout << "Revealing neighbors in all diagonal directions." << std::endl;
    for (int latOffset : verticalOffsets) {
        for (int lonOffset : horizontalOffsets) {
            int newLat = latSegmentToCheck + latOffset;
            int newLon = lonSegmentToCheck + lonOffset;

            if (newLat >= 0 && newLat < boardSize && newLon >= 0 && newLon < boardSize) {
                BoardSegment* boardSegmentToReveal = boardToReveal->grid[newLat][newLon];
                if (boardSegmentToReveal->isWater()) {
                    boardSegmentToReveal->setRevealed();
                    // Debug-Ausgabe
                    std::cout << "Revealed segment at (" << newLat << ", " << newLon << ")" << std::endl;
                }
            }
        }
    }

    switch (revealMode) {
        case 0: // North + South; above + below 
            std::cout << "Revealing neighbors in North and South direction." << std::endl;
            for (int latOffset : verticalOffsets) {
                int newLat = latSegmentToCheck + latOffset;

                if (newLat >= 0 && newLat < boardSize) {
                    BoardSegment* boardSegmentToReveal = boardToReveal->grid[newLat][lonSegmentToCheck];
                    if (boardSegmentToReveal->isWater()) {
                        boardSegmentToReveal->setRevealed();
                        // Debug-Ausgabe
                        std::cout << "Revealed segment at (" << newLat << ", " << lonSegmentToCheck << ")" << std::endl;
                    }
                }
            }
            break;

        case 1: // West + East; left + right
            std::cout << "Revealing neighbors in West and East direction." << std::endl;
            for (int lonOffset : horizontalOffsets) {
                int newLon = lonSegmentToCheck + lonOffset;

                if (newLon >= 0 && newLon < boardSize) {
                    BoardSegment* boardSegmentToReveal = boardToReveal->grid[latSegmentToCheck][newLon];
                    if (boardSegmentToReveal->isWater()) {
                        boardSegmentToReveal->setRevealed();
                        // Debug-Ausgabe
                        std::cout << "Revealed segment at (" << latSegmentToCheck << ", " << newLon << ")" << std::endl;
                    }
                }
            }
            break;

        default:
            // Ungültiger revealMode ---> Fehlerbehandlung
            std::cerr << "Invalid revealMode: " << revealMode << std::endl;
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

