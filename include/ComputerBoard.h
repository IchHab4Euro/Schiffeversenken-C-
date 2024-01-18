#ifndef COMPUTERBOARD_H
#define COMPUTERBOARD_H

#include "Board.h"
#include <iostream>
#include <ctime>

class ComputerBoard : public Board {
    public:
        ComputerBoard() : Board() {}
        void placeShips() override;
        void attack(Board* board) override;

    private:
        void revealNeighbors(Board* boardToReveal, int latSegmentToCheck, int lonSegmentToCheck, int revealMode);
        int getRandomNumber(int lowerBound, int upperBound);
        Ship* shipHit = nullptr;
        bool firstHit = false;
        bool secondHit = false;
        
        int lastHitLat = 0;
        int lastHitLon = 0;
        int latOffsetReveal = 0;
        int lonOffsetReveal = 0;
        int neighboursRevealMode = 0;
        int getRandomNumberWindows(int lowerBound, int upperBound);
};
#endif