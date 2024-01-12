#ifndef PLAYERBOARD_H
#define PLAYERBOARD_H

#include "Board.h"

#include <iostream>
#include <vector>

class PlayerBoard : public Board {
    public:
        void placeShips() override;
    
    private:
        Ship shipSelection(); 
        bool checkContainsShip(std::vector<Ship> shipList, int idToCheck);
        Ship getShipById(std::vector<Ship> shipList, int shipId);
};

#endif