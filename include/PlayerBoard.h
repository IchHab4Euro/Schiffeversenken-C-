#ifndef PLAYERBOARD_H
#define PLAYERBOARD_H

#include "Board.h"
#include "Output.h"
#include "Input.h"
#include "GameLogic.h"
#include <iostream>
#include <vector>

class PlayerBoard : public Board {
    public:
        PlayerBoard() : Board() {}
        void placeShips() override;
        //void attack(Board* board) override; 
    
    private:
        Ship* shipSelection(); 
        bool checkContainsShip(std::vector<Ship*> shipList, int idToCheck);
        Ship* getShipById(std::vector<Ship*> shipList, int shipId);
};

#endif