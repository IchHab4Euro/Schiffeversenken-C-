#ifndef PLAYERBOARD_H
#define PLAYERBOARD_H

#include "Board.h"
#include "Output.h"
#include "Input.h"
#include "GameLogic.h"
#include <iostream>
#include <vector>

/*
 class PlayerBaord inherits from Board
 represents the Board of a Player
 overrides placeShips() an attack()
*/
class PlayerBoard : public Board {
    public:
        PlayerBoard() : Board() {}
        void placeShips() override; // placing Ships
        void attack(Board* board) override; // attacking the enemy Board
        
    
    private:
        Ship* shipSelection(); //select a Ship to Place
        bool checkContainsShip(std::vector<Ship*> shipList, int idToCheck); //check if Ship is inside a List
        Ship* getShipById(std::vector<Ship*> shipList, int shipId); //returns a ship through id
        Ship* handleShipPlacementOptions(); //helper for placing Ships
        void removeShipProcedure(); //removing a ship while placing
        void removeShip(Ship* shipToRemove); //removes a ship from board
        void resetBoardPlacement(); //reseting the Board while Placing
};

#endif