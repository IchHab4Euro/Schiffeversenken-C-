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
    phase = false;
    board1->placeShips();
    board2->placeShips();
    phase = true;
    saveGame();
    Output::printPlayerBoard(board1);
    Output::printPlayerBoard(board2);

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

void GameLogic::saveGame()  {
    std::string playName;
    std::vector<Ship*> ships;
    std::cout << "Bitte gebe einen Spielname ein: " << std::endl;
    std::cin >> playName;
    if (phase == false)  {
        ships = board1->getShipsNextToBoard();
    } else  {
        ships = board1->getShipsOnBoard();
    }
    std::string saveString = playName + ";" + player1->name + ";" + std::to_string(phase) + ";" + std::to_string(ships.size()) + ";";
    for (int i = 0; i < ships.size(); i++)  {
        saveString = saveString + std::to_string(ships.at(i)->isSunken()) + ";";
    }

    saveString = saveString + std::to_string(board1->getBoardSize()) + ";";

    for(int i = 0; i < board1->getBoardSize(); i++)  {
        for (int j = 0; j < board1->getBoardSize(); j++)  {
            BoardSegment* boardsegmentP = board1->grid[i][j];
            std::string symbol;
            std::string shipID;
            if (boardsegmentP->isRevealed())  {
                symbol = "r";
                saveString = saveString + symbol + ";";
            }
            if (boardsegmentP->isShip())  {
                symbol = "s";
                shipID = std::to_string(boardsegmentP->getShipOnSegment()->getId());
                saveString = saveString + symbol + ":" + shipID + ";";
            }
            if (boardsegmentP->isShipHit())  {
                symbol = "#";
                saveString = saveString + symbol + ";";
            }
            if (boardsegmentP->isShipPlacement())  {
                symbol = "p";
                saveString = saveString + symbol + ";";
            }
            if (boardsegmentP->isWater())  {
                symbol = "w";
                saveString = saveString + symbol + ";";
            }
            if (boardsegmentP->isWaterHit())  {
                symbol = "h";
                saveString = saveString + symbol + ";";
            }
        }
    }    
    for(int i = 0; i < board2->getBoardSize(); i++)  {
        for (int j = 0; j < board1->getBoardSize(); j++)  {
            BoardSegment* boardsegmentC = board2->grid[i][j];
            std::string symbol;
            std::string shipID;
            if (boardsegmentC->isRevealed())  {
                symbol = "r";
                saveString = saveString + symbol + ";";
            }
            if (boardsegmentC->isShip())  {
                symbol = "s";
                shipID = std::to_string(boardsegmentC->getShipOnSegment()->getId());
                saveString = saveString + symbol + ":" + shipID + ";";
            }
            if (boardsegmentC->isShipHit())  {
                symbol = "#";
                saveString = saveString + symbol + ";";
            }
            if (boardsegmentC->isShipPlacement())  {
                symbol = "p";
                saveString = saveString + symbol + ";";
            }
            if (boardsegmentC->isWater())  {
                symbol = "w";
                saveString = saveString + symbol + ";";
            }
            if (boardsegmentC->isWaterHit())  {
                symbol = "h";
                saveString = saveString + symbol + ";";
            }
        }
    }    
    std::ofstream csvFile("../FieldSave.csv", std::ios_base::app);

    if (csvFile.is_open())  {
        csvFile << saveString << std::endl;
        csvFile.close();
    } else  {
        std::cout << "Datei konnte nicht ge\224ffnet werden!" << std::endl;
    } 
}

void GameLogic::loadGame() {
    

}

