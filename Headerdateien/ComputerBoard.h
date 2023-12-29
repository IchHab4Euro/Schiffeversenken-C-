#pragma once

#include "Board.h"

#include <iostream>

class ComputerBoard : public Board {
    public:
        void placeShips() override;
        
    private:
        int getRandomNumber(int lowerBound, int upperBound);
};