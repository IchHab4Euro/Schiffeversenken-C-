#pragma once

#include "Board.h"

#include <iostream>
#include <vector>

class PlayerBoard : public Board {
    public:
        void placeShips() override;
    
    private:
        bool checkContainsShip(std::vector<Ship> shipList, int idToCheck);
        Ship getShipById(std::vector<Ship> shipList, int shipId);
        void deleteShipFromVector(std::vector<Ship>& shipVector, Ship toDelete);
};