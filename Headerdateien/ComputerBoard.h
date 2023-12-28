#pragma once

#include "Board.h"

#include <iostream>

class ComputerBoard : public Board {
    public:
        void placeShips() override;
        bool placeShip(int latitude, int longitude, int direction, Ship ship) override;

    private:
        int getRandomNumber(int lowerBound, int upperBound);
};