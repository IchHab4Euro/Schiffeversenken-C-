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
            case 2: 
                loadGame();
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
    
    Output::printPlayerBoard(board1);
    Output::printPlayerBoard(board2);

    while(!(board2->allShipsSunk())){
        board1->attack(board2);
        board2->attack(board1);

        Output::printBothBoards(board1, board2);
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
    board1->init(nullptr, startingShipsPlayer);
    board2->init(nullptr, startingShipsComputer);
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
    std::ifstream csvFileName("../FieldSave.csv");
    std::vector<std::string> gameNames;

    if (csvFileName.is_open()) {
        std::string lineN;

        while (std::getline(csvFileName, lineN)) {
            std::stringstream ss(lineN);
            std::string gameName;
            if (std::getline(ss, gameName, ';')) {
                gameNames.push_back(gameName);
            }
        }
        csvFileName.close();
    }

    if (gameNames.empty())  {
        std::cout << "Es gibt keine Spielst\204nde zum laden!" << std::endl;
        return;
    }
    
    int game;
    std::ifstream csvFile("../FieldSave.csv");
    Output::printMenue(gameNames);
    game = Input::userinputInt("W\204hlen sie einen der Spielst\204nde: ", 1, gameNames.size());
    std::string line;
    if (csvFile.is_open()) {
        int zeile = 1;
        while (std::getline(csvFile, line)) {
            if (zeile == game)  {
                break;
            } else  {
                zeile++;
            }
        }
        csvFile.close();
    }
    std::cout << line << std::endl;

    std::stringstream ss(line);
    std::string tempFileInput;
    bool tempPhase;

    std::getline(ss, gameName, ';');

    std::getline(ss, tempFileInput, ';');
    player1 = new Player(tempFileInput);
    player2 = new Player("Computer");

    std::getline(ss, tempFileInput, ';');
    if (tempFileInput == "1")  {
        phase = true;
    } else  {
        phase = false;
    }
    
    //Schiffe erstellen

    board1 = new PlayerBoard();
    board2 = new ComputerBoard();

    std::getline(ss, tempFileInput, ';');
    int boardSize = std::stoi(tempFileInput);

    BoardSegment* grid[boardSize][boardSize];
    for(int lat = 0; lat < boardSize; lat++){
        for(int lon = 0; lon < boardSize; lon++){
            SegmentState segmentStateL;
            if (std::getline(ss, tempFileInput, ';') && tempFileInput == "r")  {
                segmentStateL = SegmentState::Revealed;
            }
            if (std::getline(ss, tempFileInput, ';') && tempFileInput == "s")  {
                segmentStateL = SegmentState::Ship;
            }
            if (std::getline(ss, tempFileInput, ';') && tempFileInput == "#")  {
                segmentStateL = SegmentState::ShipHit;
            }
            if (std::getline(ss, tempFileInput, ';') && tempFileInput == "p")  {
                segmentStateL = SegmentState::ShipPlacement;
            }
            if (std::getline(ss, tempFileInput, ';') && tempFileInput == "w")  {
                segmentStateL = SegmentState::Water;
            }
            if (std::getline(ss, tempFileInput, ';') && tempFileInput == "h")  {
                segmentStateL = SegmentState::WaterHit;
            }
            grid[lat][lon] = new BoardSegment(SegmentState::Water);
        }
    }

    board1->init(grid, nullptr);

}