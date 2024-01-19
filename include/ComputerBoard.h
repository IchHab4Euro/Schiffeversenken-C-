#ifndef COMPUTERBOARD_H
#define COMPUTERBOARD_H

#include "Board.h"
#include <iostream>
#include <ctime>

/*
    class ComputerBoard inherits from Board 
    represent the Board of a Computer 
    overrides the Method placeShips(), atack()
*/
class ComputerBoard : public Board {
    public:
        ComputerBoard() : Board() {}
        
        //placing all Ships 
        void placeShips() override;
        
        //atacking enemy board
        void attack(Board* enemyBoard) override;

    private:
        //reveals All Neighbous Segments arround a Ship after a Hit -> no Ships next to a other
        void revealNeighbors(Board* enemyBoardToReveal, int latSegmentToCheck, int lonSegmentToCheck, int revealMode);
        
        //returns randomNumber()
        int getRandomNumber(int lowerBound, int upperBound);
        
        Ship* shipHit = nullptr; //holds the last hitten Ship
        bool firstHit = false; //if first Hit on Ship
        bool secondHit = false; //if second Hit on Ship
        int lastHitLat = 0; //where the last Hit was Lat
        int lastHitLon = 0; //where the last Hit was Lon
        int latOffsetReveal = 0; //the direction of the ShipLat
        int lonOffsetReveal = 0; //the direction of the ShipLon
        int neighboursRevealMode = 0; //the mode how to reveal Neighbors -> depends on Ship direction
        int moveCounter = 0; //counts the lenght of the Ship

        int getRandomNumberWindows(int lowerBound, int upperBound);

        void handleFirstHit(Board* enemyBoard);
        void handleSecondHit(Board* enemyBoard);
        void handleFollowingHits(Board* enemyBoard);
        void resetHitStatus(Board* enemyBoard);
        bool isInvalidTarget (BoardSegment* segment);
        void updateSegmentStatus(BoardSegment* segment);
        void resetHitStatus();
        void setRevealDirection(int direction);
        bool isValidPosition(int lat, int lon);
        bool updateSegmentForSecondHit(BoardSegment* segment, int newLat, int newLon, Board* enemyBoard);
        void changeDirection();
};
#endif