#include "../include/ComputerBoard.h"

#include <iostream>
#include <random>
#include <vector>

void ComputerBoard::placeShips() {
    // Iterate over all ships to be placed on the board
    while (!shipsNextToBoard.empty()) {
        // Retrieve the next ship to be placed
        Ship* shipToPlace = shipsNextToBoard.front();
        shipsNextToBoard.erase(shipsNextToBoard.begin());
        std::cout << "Placing ship: " << shipToPlace->getName() << std::endl;

        bool shipPlaced = false;
        while (!shipPlaced) {
            // Generate random starting coordinates and direction
            int startLatitude = getRandomNumber(0, 9);
            int startLongitude = getRandomNumber(0, 9);
            int directionNumber = getRandomNumber(1, 4);
            Direction placementDirection = numberToDirection(directionNumber);

            // Attempt to place the ship at the generated location -> if not try again wit outher position
            shipPlaced = placeShip(startLatitude, startLongitude, placementDirection, shipToPlace);
        }

        // Add the ship to the list of ships on the board after successful placement
        shipsOnBoard.push_back(shipToPlace);
    }
}


void ComputerBoard::attack(Board* board) {
    if (!firstHit) {
       

        BoardSegment* boardSegmentToHit;
        do {
            lastHitLat = getRandomNumber(0, boardSize - 1);
            lastHitLon = getRandomNumber(0, boardSize - 1);
            boardSegmentToHit = board->grid[lastHitLat][lastHitLon];
        } while (boardSegmentToHit->isWaterHit() || boardSegmentToHit->isShipHit() || boardSegmentToHit->isRevealed());

        if (boardSegmentToHit->isWater()) {
            boardSegmentToHit->setWaterHit();
            
        }
        if (boardSegmentToHit->isShip()) {
            boardSegmentToHit->setShipHit();
            shipHit = boardSegmentToHit->getShipOnSegment();
            firstHit = true;
            
        }
    }
    else if (firstHit && !secondHit) {
        

        bool validDirectionFound = false;
        while (!validDirectionFound) {
            int revealDirection = getRandomNumber(1, 4);

            switch (revealDirection) {
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
                }
                if (boardSegmentToReveal->isShip()) { //second Hit found right direction
                   
                    boardSegmentToReveal->setShipHit();
                    lastHitLat = newLat;
                    lastHitLon = newLon;
                    revealNeighbors(board, lastHitLat, lastHitLon, neighboursRevealMode);
                    secondHit = true;
                    moveCounter++;
                    validDirectionFound = true;
                    board->setSunkenShips();
                   
                }
            }
        }
    }
    else if (shipHit != nullptr && !shipHit->isSunken() && secondHit) {


        lastHitLat = lastHitLat + latOffsetReveal;
        lastHitLon = lastHitLon + lonOffsetReveal;
        BoardSegment* boardSegmentToHit  = board->grid[lastHitLat][lastHitLon];

        if(boardSegmentToHit->isShip()) { //Ship Hit 
            boardSegmentToHit->setShipHit();
            moveCounter++;
            revealNeighbors(board, lastHitLat, lastHitLon, neighboursRevealMode);
            board->setSunkenShips();
            
        }
        else if(boardSegmentToHit->isWater()) {
            moveCounter++;
            boardSegmentToHit->setWaterHit();
          
            if(latOffsetReveal != 0) {
                latOffsetReveal = latOffsetReveal * (-1);
                lastHitLat = lastHitLat + (moveCounter * latOffsetReveal);  
            }
            if(lonOffsetReveal != 0) {
                lonOffsetReveal = lonOffsetReveal * (-1);
                lastHitLon = lastHitLon + (moveCounter * lonOffsetReveal);  
            }
            moveCounter = 0;

            
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
        }
    }
    if (shipHit != nullptr && shipHit->isSunken()) {
        shipHit = nullptr;
        firstHit = false;
        secondHit = false;
        moveCounter = 0;
    }
}


void ComputerBoard::revealNeighbors(Board* enemyBoardToReveal, int latSegmentToCheck, int lonSegmentToCheck, int revealMode) {
    const int verticalOffsets[] = {-1, 1};
    const int horizontalOffsets[] = {-1, 1};

    // Diagonalen immer aufdecken
    for (int latOffset : verticalOffsets) {
        for (int lonOffset : horizontalOffsets) {
            int newLat = latSegmentToCheck + latOffset;
            int newLon = lonSegmentToCheck + lonOffset;

            if (newLat >= 0 && newLat < boardSize && newLon >= 0 && newLon < boardSize) {
                BoardSegment* boardSegmentToReveal = enemyBoardToReveal->grid[newLat][newLon];
                if (boardSegmentToReveal->isWater()) {
                    boardSegmentToReveal->setRevealed();
                }
            }
        }
    }

    switch (revealMode) {
        case 0: // North + South; above + below 
            for (int latOffset : verticalOffsets) {
                int newLat = latSegmentToCheck + latOffset;

                if (newLat >= 0 && newLat < boardSize) {
                    BoardSegment* boardSegmentToReveal = enemyBoardToReveal->grid[newLat][lonSegmentToCheck];
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
                    BoardSegment* boardSegmentToReveal = enemyBoardToReveal->grid[latSegmentToCheck][newLon];
                    if (boardSegmentToReveal->isWater()) {
                        boardSegmentToReveal->setRevealed();
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

