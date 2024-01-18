#include "../include/GameLogic.h"

int Player::nextID = 0;

Player::Player(std::string name) : name(name) {
    playerID = this->nextID;
    this->nextID++;
}

GameLogic::GameLogic() {
    this->output = new Output();
}

void GameLogic::init() { //vlt umbennen zu
    //std::signal(SIGINT,signal_handler); Autosafe aktivieren
    output->printWelcome(); //Todo: Press any Button to Continue, danach clear
    //Todo: Check for Autosafe
    //Todo: AutoSave durchführen
    char inputMenu;
    std::vector<std::string> menuePoints {"New Game", "Load Game", "Settings", "Exit"};
    while(1) {
        output->printMenue(menuePoints); //Todo: Zahlen vor die Menüopunkte + Zentral Ausrichten + Text drunter, dass Zahl eingeben soll
        std::cin >> inputMenu;
        switch (inputMenu) {
            case '1': //New Game 
                newGame();
                break;
            case '2': //Load Game 
                //Todo: Print verfügbaren Speicherstände
                break;
            case '3': //Exit
                //Todo: Settings
                break;
            case '4':
                exit(1);
                break;
            default:
                //Todo: print Error
                output->printBoxError("Falsche Auswahl");
                break;
        }
    }
}

void GameLogic::startGame(){
    //board1->placeShips();
    board2->placeShips();

    //output->printPlayerBoard(board1);
    output->printPlayerBoard(board2);
}

void GameLogic::newGame() {
    //Todo: Spielernamen abfragen 
    player1 = new Player("Rumpelstielschen");
    player2 = new Player("Computer");
    board1 = new PlayerBoard();
    board2 = new ComputerBoard();
    board1->init(startingShips);
    board2->init(startingShips);
    startGame();
}

void GameLogic::loadGame() {

}

