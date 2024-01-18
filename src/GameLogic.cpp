#include "../include/GameLogic.h"

int Player::nextID = 0;

Player::Player(std::string name) : name(name) {
    playerID = this->nextID;
    this->nextID++;
}

GameLogic::GameLogic() {
}

void GameLogic::init() { //vlt umbennen zu
    //std::signal(SIGINT,signal_handler); Autosafe aktivieren
    Output::printWelcome(); //Todo: Press any Button to Continue, danach clear
    //Todo: Check for Autosafe
    //Todo: AutoSave durchführen
    int inputMenu;
    std::vector<std::string> menuePoints {"New Game", "Load Game", "Settings", "Exit"};
    while(1) {
        Output::printMenue(menuePoints);
        inputMenu = Input::userinputInt("Bitte w\204hlen sie einen Men\201 Punkt aus: ", 1, menuePoints.size());
        switch (inputMenu) {
            case 1: //New Game 
                newGame();
                break;
            case 2: //Load Game 
                //Todo: Print verfügbaren Speicherstände
                break;
            case 3: //Exit
                //Todo: Settings
                break;
            case 4:
                exit(1);
                break;
            default:
                //Todo: print Error
                Output::printBoxError("Falsche Auswahl", false);
                break;
        }
    }
}

void GameLogic::startGame(){
    board1->placeShips();
    board2->placeShips();

    Output::printPlayerBoard(board1);
    Output::printPlayerBoard(board2);

        while(!(board1->allShipsSunk()) || !(board2->allShipsSunk())){
        board1->attack(board2);
        board2->attack(board1);

        Output::printPlayerBoard(board1);
        Output::printPlayerBoard(board2);
    }

}
    

void GameLogic::newGame() {
    //Todo: Spielernamen abfragen 
    player1 = new Player("Rumpelstielschen");
    player2 = new Player("Computer");
    board1 = new ComputerBoard();
    board2 = new ComputerBoard();
    board1->init(startingShips);
    board2->init(startingShips);
    startGame();
}

void GameLogic::loadGame() {
    

}

