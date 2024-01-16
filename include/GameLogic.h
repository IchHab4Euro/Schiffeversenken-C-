#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "../include/GameLogic.h"
#include "../include/Output.h"
#include "../include/PlayerBoard.h"
#include "../include/ComputerBoard.h"
#include <csignal>

struct Player {
    Player(std::string name) : name(name) {
        playerID = nextID;
        nextID++;
    }
    int playerID;
    std::string name;
    static int nextID;
};

class GameLogic {
    public:
        GameLogic();
        //~GameLogic();
        void init();
        
    private:
        Output* output;
        Board* board1;
        Board* board2;
        Player* player1;
        Player* player2;

        void menue();
        void newGame();
        void loadGame();
        void startGame();
};
    //void signal_handler(int signal);
#endif