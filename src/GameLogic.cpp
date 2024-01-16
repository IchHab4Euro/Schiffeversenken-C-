#include "../include/GameLogic.h"

GameLogic::GameLogic() {
    this->output = new Output();
}

void GameLogic::init() {
    //std::signal(SIGINT,signal_handler); Autosafe aktivieren
    output->printWelcome();
    //Todo: Check for Autosafe

    //Menu
    char input;
    std::vector<std::string> menuePoints {"Neues Spiel", "Spiel Laden"};
    while(1) {
        output->printMenue(menuePoints);
    }
}

void GameLogic::startGame(){
    
}

void GameLogic::newGame() {
    board1 = new PlayerBoard();
    board2 = new ComputerBoard();
}

void GameLogic::loadGame() {

}

