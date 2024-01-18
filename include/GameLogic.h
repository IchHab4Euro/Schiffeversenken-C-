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

        std::vector<Ship*> startingShips = {
            new Ship("Schlachtschiff", 5, false), new Ship("Kreuzer1", 4, false), new Ship("Kreuzer2", 4, false),
            new Ship("Testschiff", 2, false)
        };

        void newGame();
        void loadGame();
        void startGame();
};
    //void signal_handler(int signal);
#endif