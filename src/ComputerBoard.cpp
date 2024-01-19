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


/*
void ComputerBoard::attack(Board* enemyBoard) {
    // If it's the first attack
    if (!firstHit) {
        std::cout << "Entering initial attack phase..." << std::endl;

        BoardSegment* targetSegment;
        do {
            // Randomly select a target segment
            lastHitLat = getRandomNumber(0, boardSize - 1);
            lastHitLon = getRandomNumber(0, boardSize - 1);
            targetSegment = enemyBoard->grid[lastHitLat][lastHitLon];
        } while (targetSegment->isWaterHit() || targetSegment->isShipHit() || targetSegment->isRevealed());

        // Process the attack based on the type of segment
        processAttack(targetSegment);
    }
    else if (firstHit && !secondHit) {
        std::cout << "Entering second hit phase..." << std::endl;
        attemptSecondHit(enemyBoard);
    }
    else if (firstHit && secondHit) {
        std::cout << "Continuing to attack previously hit ship..." << std::endl;
        continueAttackOnShip(enemyBoard);
    }

    enemyBoard->setSunkenShips(); //updating all Ships on enemy Board

    // Reset attack state if the ship is sunken
    if (shipHit != nullptr && shipHit->isSunken()) {
        resetAttackState();
    }
}

void ComputerBoard::processAttack(BoardSegment* targetSegment) {
    if (targetSegment->isWater()) {
        targetSegment->setWaterHit();
        std::cout << "Hit water at (" << lastHitLat << ", " << lastHitLon << ")" << std::endl;
    }
    if (targetSegment->isShip()) {
        targetSegment->setShipHit();
        shipHit = targetSegment->getShipOnSegment();
        firstHit = true;
        std::cout << "Hit ship at (" << lastHitLat << ", " << lastHitLon << ")" << std::endl;
    }
}

void ComputerBoard::attemptSecondHit(Board* enemyBoard) {
    /*
    second hit phase -> he looks for the second ship segment.
    If it is a hit the direction is reveales.
    For every hit the Neigbours will be revealed.
    */
/*
    // Debug-Ausgabe
    std::cout << "Entering second hit phase..." << std::endl;

    bool validDirectionFound = false;
    while (!validDirectionFound) {
        int revealDirection = getRandomNumber(1, 4); //picks a random dircection

        switch (revealDirection) { //direction leads to offset and the mode of revealing Neighours
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

        //new Location to try a hit
        int newLat = lastHitLat + latOffsetReveal; 
        int newLon = lastHitLon + lonOffsetReveal;

        //check if Location is in grid
        if (newLat >= 0 && newLat < boardSize && newLon >= 0 && newLon < boardSize) { 
            BoardSegment* boardSegmentToReveal = enemyBoard->grid[newLat][newLon];
            std::cout << "Completet Check for number in grid newLat: " << newLat << "new Lon: " << newLon << std::endl;

            //hitting the Watter chanhing state of Segment
            if (boardSegmentToReveal->isWater()) {
                boardSegmentToReveal->setWaterHit();
                validDirectionFound = true;
                // Debug-Ausgabe
                std::cout << "Hit water at (" << newLat << ", " << newLon << ")" << std::endl;
            }
            
            //hitting Ship changing state of Segment
            if (boardSegmentToReveal->isShip()) { //second Hit -> found the direction of the ship 
                // Debug-Ausgabe
                std::cout << "Trying to hit Ship at (" << newLat << ", " << newLon << ")" << std::endl;
                boardSegmentToReveal->setShipHit();
                lastHitLat = newLat;
                lastHitLon = newLon;
                revealNeighbors(enemyBoard, lastHitLat, lastHitLon, neighboursRevealMode);//revealing Neighbours after Hit
                secondHit = true; //now second hit is also true
                moveCounter++; //increase the counter to track how long the ship is, for changing direction
                validDirectionFound = true;
                //board->setSunkenShips();
                // Debug-Ausgabe
                std::cout << "Hit ship at (" << newLat << ", " << newLon << ")" << std::endl;
            }
        }
    }    
}

void ComputerBoard::continueAttackOnShip(Board* enemyBoard) {
    /*
    3. Attack Phase: Goes along the ship (throgh direction found in previosly attacks), condition ship is not sunken 
    If the ship ends with water -> changing direcion after hitting water
    If the ship ends with a revealed/waterhit segment -> change direcion and hit the ship.
    */

   /*
    // Debug-Ausgabe
    std::cout << "Continuing to attack previously hit ship..." << std::endl;

    int newLat = lastHitLat + latOffsetReveal;
    int newLon = lastHitLon + lonOffsetReveal;
    moveCounter++;

    if (newLat >= 0 && newLat < boardSize && newLon >= 0 && newLon < boardSize) {
        BoardSegment* boardSegmentToReveal = enemyBoard->grid[newLat][newLon];
            
        if(boardSegmentToReveal->isShip()) { //Ship Hit 
            boardSegmentToReveal->setShipHit();
            revealNeighbors(enemyBoard, lastHitLat, lastHitLon, neighboursRevealMode);
            
            // Debug-Ausgabe
            std::cout << "Continuing attack on ship at (" << lastHitLat << ", " << lastHitLon << ")" << std::endl;    
        }
        if(boardSegmentToReveal->isWater()) {
            boardSegmentToReveal->setWaterHit();

            // Debug-Ausgabe
            std::cout << "Hit water at (" << lastHitLat << ", " << lastHitLon << ")" << std::endl;
        
            //Changing Directions
            if(latOffsetReveal != 0) { //North <-> South
                latOffsetReveal = latOffsetReveal * (-1);
                lastHitLat = lastHitLat + (moveCounter * latOffsetReveal); 
            }
            if(lonOffsetReveal != 0) { //East <-> West
                lonOffsetReveal = lonOffsetReveal * (-1);
                lastHitLon = lastHitLon + (moveCounter * lonOffsetReveal);  
            }
            moveCounter = 0;

            // Debug-Ausgabe
            std::cout << "neuer lastHit nach Richtungswechsel wegen Wasser(" << lastHitLat << ", " << lastHitLon << ")" << std::endl; 
        }
    }
    else {
        if(latOffsetReveal != 0) {
                latOffsetReveal = latOffsetReveal * (-1);
                lastHitLat = lastHitLat + moveCounter * latOffsetReveal;  
            }
            if(lonOffsetReveal != 0) {
                lonOffsetReveal = lonOffsetReveal * (-1);
                lastHitLon = lastHitLon + moveCounter * lonOffsetReveal;  
            }
        moveCounter = 0;
        attack(enemyBoard);
        // Debug-Ausgabe
        std::cout << "Changing attack direction due to obstacle." << std::endl;
    }

}
    
//reseting Attack State after sinking a enemy Ship
void ComputerBoard::resetAttackState() {
    shipHit = nullptr;
    firstHit = false;
    secondHit = false;
    moveCounter = 0;
    std::cout << "Resetting attack state after sinking a ship." << std::endl;
}
*/

void ComputerBoard::revealNeighbors(Board* enemyBoardToReveal, int latSegmentToCheck, int lonSegmentToCheck, int revealMode) {
    const int verticalOffsets[] = {-1, 1};
    const int horizontalOffsets[] = {-1, 1};

    // Diagonalen immer aufdecken
    std::cout << "Revealing neighbors in all diagonal directions." << std::endl;
    for (int latOffset : verticalOffsets) {
        for (int lonOffset : horizontalOffsets) {
            int newLat = latSegmentToCheck + latOffset;
            int newLon = lonSegmentToCheck + lonOffset;

            if (newLat >= 0 && newLat < boardSize && newLon >= 0 && newLon < boardSize) {
                BoardSegment* boardSegmentToReveal = enemyBoardToReveal->grid[newLat][newLon];
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
                    BoardSegment* boardSegmentToReveal = enemyBoardToReveal->grid[newLat][lonSegmentToCheck];
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
                    BoardSegment* boardSegmentToReveal = enemyBoardToReveal->grid[latSegmentToCheck][newLon];
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

