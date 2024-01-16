#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "../include/GameLogic.h"
#include "../include/Output.h"
#include "../include/PlayerBoard.h"
#include "../include/ComputerBoard.h"
#include <csignal>

struct Player {
    Player(std::string name);
    int playerID;
    std::string name;
};

class GameLogic {
    public:
        GameLogic();
        //~GameLogic();
        void init();
        void startGame();
    private:
        Output* output;
        Board* board1;
        Board* board2;

        void newGame();
        void loadGame();
};
    //void signal_handler(int signal);
#endif