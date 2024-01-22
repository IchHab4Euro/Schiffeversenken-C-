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

void ComputerBoard::attack(Board* enemyBoard) {
    if (!firstHit) { //if no ship is found
        handleFirstHit(enemyBoard);
    } else if (firstHit && !secondHit) {//ship found direction unknown
        handleSecondHit(enemyBoard);
    } else if (firstHit && secondHit) {// ship found direction known
        handleFollowingHits(enemyBoard);
    }

    if (shipHit != nullptr && shipHit->isSunken()) { //if ship is sunken
        resetHitStatus();
    }
    enemyBoard->setSunkenShips();
}

void ComputerBoard::handleFirstHit(Board* enemyBoard) {
    BoardSegment* targetSegment;
    do {
        lastHitLat = getRandomNumber(0, boardSize - 1);
        lastHitLon = getRandomNumber(0, boardSize - 1);
        targetSegment = enemyBoard->grid[lastHitLat][lastHitLon];
    } while (isInvalidTarget(targetSegment)); //randomly select a segment until you find one that has not yet been shot at or is known.

    updateSegmentStatus(targetSegment);
}

void ComputerBoard::handleSecondHit(Board* enemyBoard) {
    bool validDirectionFound = false;
    while (!validDirectionFound) { //until finding one that has not yet been shot at, is known or outside of the grid
        setRevealDirection(getRandomNumber(1, 4)); //picking a random direction
        int newLat = lastHitLat + latOffsetReveal; //direction through offset
        int newLon = lastHitLon + lonOffsetReveal;

        if (isValidPosition(newLat, newLon)) { //checking if new position is in the grid Bounds
            BoardSegment* segmentToReveal = enemyBoard->grid[newLat][newLon];
            validDirectionFound = updateSegmentForSecondHit(segmentToReveal, newLat, newLon, enemyBoard);//true if it is a fireable target Segment
        }
    }
}

void ComputerBoard::handleFollowingHits(Board* enemyBoard) {
    lastHitLat = lastHitLat + latOffsetReveal; //the direction of the ship is known
    lastHitLon = lastHitLon + lonOffsetReveal;
    moveCounter++;
    if(isValidPosition(lastHitLat,lastHitLon)) { //inside grid bounds
        BoardSegment* boardSegmentToHit  = enemyBoard->grid[lastHitLat][lastHitLon];
        if(isInvalidTarget(boardSegmentToHit)){ //the next segment is known
            changeDirection();
            handleFollowingHits(enemyBoard); //new shot
        }
        if(boardSegmentToHit->isWater()){
            boardSegmentToHit->setWaterHit(); 
            changeDirection();
        }
        if(boardSegmentToHit->isShip()){
            boardSegmentToHit->setShipHit();
            revealNeighbors(enemyBoard,lastHitLat,lastHitLon,neighboursRevealMode);
        }
    }
    else {
        changeDirection(); //if new position is outside grid bounds
        handleFollowingHits(enemyBoard);
    }
}

void ComputerBoard::changeDirection() { //changing directieon 
    if(latOffsetReveal != 0) { //Nort <-> South
        latOffsetReveal = latOffsetReveal * (-1);
        lastHitLat = lastHitLat + moveCounter * latOffsetReveal; //set new position in the outher direction
        }
    if(lonOffsetReveal != 0) { //East <-> West
        lonOffsetReveal = lonOffsetReveal * (-1);
        lastHitLon = lastHitLon + moveCounter * lonOffsetReveal;  
        }
        moveCounter = 0;
}
    

void ComputerBoard::resetHitStatus() { //after a ship has sunk
    shipHit = nullptr;
    firstHit = false;
    secondHit = false;
    moveCounter = 0;
}

bool ComputerBoard::isInvalidTarget(BoardSegment* segment) { //checks if the Target is known 
    return segment->isWaterHit() || segment->isShipHit() || segment->isRevealed();
}

void ComputerBoard::updateSegmentStatus(BoardSegment* segment) {
    if (segment->isWater()) {//water Hit
        segment->setWaterHit();
    } else if (segment->isShip()) {//ship Hit
        segment->setShipHit();
        shipHit = segment->getShipOnSegment();
        firstHit = true;
    }
}

void ComputerBoard::setRevealDirection(int direction) { //sets the variables for the matching direction
    switch (direction) {
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
}

bool ComputerBoard::isValidPosition(int lat, int lon) { //checks if position is inside grid bounds.
    return lat >= 0 && lat < boardSize && lon >= 0 && lon < boardSize;
}

bool ComputerBoard::updateSegmentForSecondHit(BoardSegment* segment, int newLat, int newLon, Board* enemyBoard) {
    if (segment->isWater()) { //Water Hit
        segment->setWaterHit();
        return true;
    }
    if (segment->isShip()) { //Ship Hit
        segment->setShipHit();
        lastHitLat = newLat;
        lastHitLon = newLon;
        revealNeighbors(enemyBoard, lastHitLat, lastHitLon,neighboursRevealMode);
        secondHit = true;
        moveCounter++;
        return true;
    }
    return false;//already hit or uncovered
}

void ComputerBoard::revealNeighbors(Board* enemyBoardToReveal, int latSegmentToCheck, int lonSegmentToCheck, int revealMode) {
    const int verticalOffsets[] = {-1, 1};
    const int horizontalOffsets[] = {-1, 1};

    // Always uncover diagonals
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
            //Wrong revealMode ---> Fehlerbehandlung
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

