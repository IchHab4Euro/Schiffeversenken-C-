#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "GameLogic.h"
#include "Output.h"
#include "Board.h"
#include "PlayerBoard.h"
#include "ComputerBoard.h"
#include "Ship.h"
#include <csignal>
#include <sstream>
#include <fstream>
#include <random>

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

        void initShipConf();

        Board* board1;
        Board* board2;
        Player* player1;
        Player* player2;
        std::string gameName;

        void newGame();
        void saveGame();
        void loadGame();
        void startGame();
    private:
        bool gamePhase = false;
        int getRandomNumber(int lowerBound, int upperBound);

        std::vector<Ship*> shipConf1Player;
        std::vector<Ship*> shipConf1Computer;

        std::vector<Ship*> shipConf2Player;
        std::vector<Ship*> shipConf2Computer;

        std::vector<Ship*> shipConf3Player;
        std::vector<Ship*> shipConf3Computer;
};
    //void signal_handler(int signal);
#endif