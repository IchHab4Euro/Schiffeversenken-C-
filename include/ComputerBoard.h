#ifndef COMPUTERBOARD_H
#define COMPUTERBOARD_H

#include "Board.h"
#include <iostream>
#include <ctime>

/*
    class ComputerBoard inherits from Board 
    represent the Board of a Computer 
    overrides the Methods placeShips(), atack()
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

        //Helper-Methods for the attack
        void handleFirstHit(Board* enemyBoard); //randomly hitting the enemy Board. Hitting Ship -> firstHit = true
        void handleSecondHit(Board* enemyBoard); //looking for a second ship element. secondHit -> safe the dircetion of the ship
        void handleFollowingHits(Board* enemyBoard); //if firstHit + secondHit -> Direction is known -> Attacking Ship until it is sunk
        bool isInvalidTarget (BoardSegment* segment); //checking weather the segment alredy has been hit or is reveales
        void updateSegmentStatus(BoardSegment* segment); //Water Segment -> Water Hit, Ship -> Ship Hit
        void resetHitStatus(); //after Ship is sunk -> resseting variables
        void setRevealDirection(int direction); //sets variables through direction
        bool isValidPosition(int lat, int lon); //checks if posiotion is inside grind bounds
        bool updateSegmentForSecondHit(BoardSegment* segment, int newLat, int newLon, Board* enemyBoard); //ship or water hit -> true
        void changeDirection(); //modify variables for new direcion -> new position 
        
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

        
};
#endif