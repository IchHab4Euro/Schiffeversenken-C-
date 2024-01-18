#ifndef COMPUTERBOARD_H
#define COMPUTERBOARD_H

#include "Board.h"
#include <iostream>
#include <ctime>

class ComputerBoard : public Board {
    public:
        ComputerBoard() : Board() {}
        void placeShips() override;

    private:
        int getRandomNumber(int lowerBound, int upperBound);
        int getRandomNumberWindows(int lowerBound, int upperBound);
};
#endif