#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "GameLogic.h"
#include "Output.h"
#include "Board.h"
#include "PlayerBoard.h"
#include "ComputerBoard.h"
#include "Ship.h"
#include <csignal>

struct Player {
    Player(std::string name);
    static int nextID;
    int playerID;
    std::string name;
};

class GameLogic {
    public:
        GameLogic();
        //~GameLogic();
        void init();

        Board* board1;
        Board* board2;
        Player* player1;
        Player* player2;

        void newGame();
        void loadGame();
        void startGame();
};
    //void signal_handler(int signal);
#endif