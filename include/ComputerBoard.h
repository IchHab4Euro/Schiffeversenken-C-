#ifndef COMPUTERBOARD_H
#define COMPUTERBOARD_H

#include "Board.h"
#include <iostream>

class ComputerBoard : public Board {
    public:
        ComputerBoard() : Board() {}
        void placeShips() override;

    private:
        int getRandomNumber(int lowerBound, int upperBound);
};
#endif