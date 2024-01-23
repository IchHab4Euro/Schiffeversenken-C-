#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#define SAFEFILE "../FieldSave.csv"

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

/*
    struct Player
    represents a Player
*/
struct Player {
    Player(std::string name);
    static int nextID;
    int playerID;
    std::string name;
};

/*
    class GameLogic
    Controlls the running Game
*/
class GameLogic {
    public:
        GameLogic();
        
        //init the alle needed relations
        void init();

        //inits all avialable ShipConfigs
        void initShipConf();

        Board* board1;
        Board* board2;
        Player* player1;
        Player* player2;
        static inline GameLogic* sigObj;

        //starts a new Game
        void newGame();
        
        //saves a Game
        void saveGame();
        
        //loads a Game
        void loadGame();
        
        //starting a Game after new Game or load Game
        void startGame();
        
    private:
        //hold the game Phase true = placment Phase; false = attacking Phase
        bool gamePhase = false;
        int shipConfigChoice = 1;
        int gameMode = 1;
        std::string gameName = "AUTOSAFE";
        int getRandomNumber(int lowerBound, int upperBound);
        void loadAutosafe();
        void deleteAutosafe();
        void settings();

        //the predefined Konfigs of Ships, different number of Ships
        std::vector<Ship*> shipConf1Player;
        std::vector<Ship*> shipConf1Computer;

        std::vector<Ship*> shipConf2Player;
        std::vector<Ship*> shipConf2Computer;

        std::vector<Ship*> shipConf3Player;
        std::vector<Ship*> shipConf3Computer;
};
    void signal_handler(int signal);
#endif