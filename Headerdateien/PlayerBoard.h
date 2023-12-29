#pragma once

#include "Board.h"

#include <iostream>

class PlayerBoard : public Board {
    public:
        void placeShips() override;
    
    private:
        bool checkContainsShip(std::vector<Ship> shipList, int idToCheck);
        Ship getShipById(std::vector<Ship> shipList, int shipId);
};