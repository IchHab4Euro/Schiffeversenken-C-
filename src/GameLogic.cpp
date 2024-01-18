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
    char inputMenu;
    std::vector<std::string> menuePoints {"New Game", "Load Game", "Settings", "Exit"};
    while(1) {
        Output::printMenue(menuePoints); //Todo: Zahlen vor die Menüopunkte + Zentral Ausrichten + Text drunter, dass Zahl eingeben soll
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
                Output::printBoxError("Falsche Auswahl");
                break;
        }
    }
}

void GameLogic::startGame(){
    board1->placeShips();
    board2->placeShips();

    //Output::printPlayerBoard(board1);
    //Output::printPlayerBoard(board2);

    while(!(board1->allShipsSunk())){
        board1->attack(board2);
        //board2->attack(board1);

        Output::printPlayerBoard(board1);
        //Output::printPlayerBoard(board2);
        }
    }
    

void GameLogic::newGame() {
    
    /*std::vector<Ship*> startingShipsPlayer = {
            new Ship("Schlachtschiff", 5, false), new Ship("Kreuzer1", 4, false), new Ship("Kreuzer2", 4, false),
            new Ship("Testschiff", 2, false)
        };
    std::vector<Ship*> startingShipsComputer = {
            new Ship("Schlachtschiff", 5, false), new Ship("Kreuzer1", 4, false), new Ship("Kreuzer2", 4, false),
            new Ship("Testschiff", 2, false)
        };
        */
    std::vector<Ship*> startingShipsPlayer = {
            new Ship("Schlachtschiff", 8, false)
        };
    std::vector<Ship*> startingShipsComputer = {
            new Ship("Testschiff", 2, false)
        };
        

    
    //Todo: Spielernamen abfragen
    player1 = new Player("Rumpelstielschen");
    player2 = new Player("Computer");
    board1 = new PlayerBoard();
    board2 = new ComputerBoard();
    board1->init(startingShipsPlayer);
    board2->init(startingShipsComputer);
    startGame();
}

void GameLogic::loadGame() {
    

}

