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

    if(!gamePhase){
        board1->placeShips();
        board2->placeShips();
    
        Output::printPlayerBoard(board1);
        Output::printPlayerBoard(board2);
        gamePhase = true;
        saveGame();
    }


    while(!(board2->allShipsSunk())){
        board1->attack(board2);
        board2->attack(board1);

        Output::printBothBoards(board1, board2);
    }
}
    

void GameLogic::newGame() {
    std::vector<Ship*> startingShipsPlayer = {
            new Ship("Schlachtschiff", 8, false), new Ship("Dampfer",3,false)
        };
    std::vector<Ship*> startingShipsComputer = {
            new Ship("Testschiff", 2, false)
        };

    //Todo: Spielernamen abfragen
    player1 = new Player("Rumpelstielschen");
    player2 = new Player("Computer");

    std::vector<BoardSegment*> initSegments;

    board1 = new PlayerBoard();
    board2 = new ComputerBoard();

    for(int i = 0; i < (board1->getBoardSize() * board1->getBoardSize()); i++) {
        initSegments.push_back(new BoardSegment(SegmentState::Water));
    }
    board1->init(initSegments, startingShipsPlayer);
    initSegments.clear();
    for(int i = 0; i < (board2->getBoardSize() * board2->getBoardSize()); i++) {
        initSegments.push_back(new BoardSegment(SegmentState::Water));
    }
    board2->init(initSegments, startingShipsComputer);
    gamePhase = false;
    startGame();
}

void GameLogic::saveGame()  {
    std::string playName;
    std::vector<Ship*> ships;
    std::cout << "Bitte gebe einen Spielname ein: " << std::endl;
    std::cin >> playName;
    if (gamePhase == false)  {
    std::string gamePhaseValue;

    //String: Spielname;Spielername;Phase
    //Wenn Schiffe nicht geplaced 0 wenn geplaced 1
    ships = board1->getShipsOnBoard();
    if (gamePhase == false)  {
        gamePhaseValue = "0";
    } else  {
        gamePhaseValue = "1";
    }
    std::string saveString = playName + ";" + player1->name + ";" + std::to_string(gamePhase) + ";" + std::to_string(ships.size()) + ";";
    std::string saveString = playName + ";" + player1->name + ";" + gamePhaseValue + ";";
    
    //Shipconfig: Schiffsanzahl;S1Sunken;S2Sunken,S3Sunken
    std::string shipconfig;
    shipconfig = std::to_string(ships.size()) + ";";

    for (int i = 0; i < ships.size(); i++)  {
        std::cout << ships.at(i)->getName();
        shipconfig = shipconfig + std::to_string(ships.at(i)->isSunken()) + ";"; //sunk == 1 wenn gesunken
    }

    //ComputerString
    ships = board2->getShipsOnBoard();

    for (int i = 0; i < ships.size(); i++)  {
        shipconfig = shipconfig + std::to_string(ships.at(i)->isSunken()) + ";";
    }

    saveString = saveString + shipconfig + std::to_string(board1->getBoardSize()) + ";";


    std::string boardStringPlayer;
    for(int i = 0; i < board1->getBoardSize(); i++)  {
        for (int j = 0; j < board1->getBoardSize(); j++)  {
            BoardSegment* boardsegmentP = board1->grid[i][j];
            std::string symbol;
            std::string shipID;
            if (boardsegmentP->isRevealed())  {
                symbol = "r";
                boardStringPlayer = boardStringPlayer + symbol + ";";
            }
            if (boardsegmentP->isShip())  {
                symbol = "s";
                shipID = std::to_string(boardsegmentP->getShipOnSegment()->getId());
                boardStringPlayer = boardStringPlayer + symbol + ":" + shipID + ";";
            }
            if (boardsegmentP->isShipHit())  {
                symbol = "#";
                boardStringPlayer = boardStringPlayer + symbol + ";";
            }
            if (boardsegmentP->isShipPlacement())  {
                symbol = "p";
                boardStringPlayer = boardStringPlayer + symbol + ";";
            }
            if (boardsegmentP->isWater())  {
                symbol = "w";
                boardStringPlayer = boardStringPlayer + symbol + ";";
            }
            if (boardsegmentP->isWaterHit())  {
                symbol = "h";
                boardStringPlayer = boardStringPlayer + symbol + ";";
            }
        }
    }  

    saveString = saveString + boardStringPlayer;

    std::string boardStringComputer;
    for(int i = 0; i < board2->getBoardSize(); i++)  {
        for (int j = 0; j < board1->getBoardSize(); j++)  {
            BoardSegment* boardsegmentC = board2->grid[i][j];
            std::string symbol;
            std::string shipID;
            if (boardsegmentC->isRevealed())  {
                symbol = "r";
                boardStringComputer = boardStringComputer + symbol + ";";
            }
            if (boardsegmentC->isShip())  {
                symbol = "s";
                shipID = std::to_string(boardsegmentC->getShipOnSegment()->getId());
                boardStringComputer = boardStringComputer + symbol + ":" + shipID + ";";
            }
            if (boardsegmentC->isShipHit())  {
                symbol = "#";
                boardStringComputer = boardStringComputer + symbol + ";";
            }
            if (boardsegmentC->isShipPlacement())  {
                symbol = "p";
                boardStringComputer = boardStringComputer + symbol + ";";
            }
            if (boardsegmentC->isWater())  {
                symbol = "w";
                boardStringComputer = boardStringComputer + symbol + ";";
            }
            if (boardsegmentC->isWaterHit())  {
                symbol = "h";
                boardStringComputer = boardStringComputer + symbol + ";";
            }
        }    
    }

    saveString = saveString + boardStringPlayer;

    std::ofstream csvFile("../FieldSave.csv", std::ios_base::app);

    if (csvFile.is_open())  {
        csvFile << saveString << std::endl;
        csvFile.close();
    } else  {
        std::cout << "Datei konnte nicht ge\224ffnet werden!" << std::endl;
    }   
}
}

/*
void GameLogic::loadGame() {
    std::ifstream csvFileName("../FieldSave.csv");
    std::vector<std::string> gameNames;
    std::string gameName;

    if (csvFileName.is_open()) {
        std::string lineN;

        while (std::getline(csvFileName, lineN)) {
            std::stringstream ss(lineN);
            
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
       gamePhase = true;
    } else  {
       gamePhase = false;
    }

    std::getline(ss, tempFileInput, ';');
    int shipNumber = std::stoi(tempFileInput);
    std::vector<Ship*> startingShipsPlayer;
    std::vector<Ship*> startingshipsComputer;
    switch (shipNumber)  {
    case 1:
        //Pattern1
        break;
    case 3:
        //Pattern2
        break;
    case 5:
        //Pattern3
        break;
    case 7:
        //Pattern4
        break;
    case 10:
        //Pattern5
        break;    
    default:
        break;
    }

    board1 = new PlayerBoard();
    board2 = new ComputerBoard();

    std::getline(ss, tempFileInput, ';');
    int boardSize = std::stoi(tempFileInput);
    std::vector<BoardSegment*> initSegments;
    
    for(int i = 0; i < (board1->getBoardSize() * board1->getBoardSize()); i++) {
        if (std::getline(ss, tempFileInput, ';') && tempFileInput == "r")  {
                initSegments.push_back(new BoardSegment(SegmentState::Revealed));
        }
        if (std::getline(ss, tempFileInput, ';') && tempFileInput == "s")  {
                initSegments.push_back(new BoardSegment(SegmentState::Ship));
                
        }
        if (std::getline(ss, tempFileInput, ';') && tempFileInput == "#")  {
            initSegments.push_back(new BoardSegment(SegmentState::ShipHit));
        }
        if (std::getline(ss, tempFileInput, ';') && tempFileInput == "p")  {
            initSegments.push_back(new BoardSegment(SegmentState::ShipPlacement));
         }
        if (std::getline(ss, tempFileInput, ';') && tempFileInput == "w")  {
            initSegments.push_back(new BoardSegment(SegmentState::Water));
        }
        if (std::getline(ss, tempFileInput, ';') && tempFileInput == "h")  {
            initSegments.push_back(new BoardSegment(SegmentState::WaterHit));
        }     
    }
    board1->init(initSegments, startingShipsPlayer);
    initSegments.clear();
    
    for(int i = 0; i < (board2->getBoardSize() * board2->getBoardSize()); i++) {
        if (std::getline(ss, tempFileInput, ';') && tempFileInput == "r")  {
                initSegments.push_back(new BoardSegment(SegmentState::Revealed));
        }
        if (std::getline(ss, tempFileInput, ';') && tempFileInput == "s")  {
                initSegments.push_back(new BoardSegment(SegmentState::Ship));
        }
        if (std::getline(ss, tempFileInput, ';') && tempFileInput == "#")  {
            initSegments.push_back(new BoardSegment(SegmentState::ShipHit));
        }
        if (std::getline(ss, tempFileInput, ';') && tempFileInput == "p")  {
            initSegments.push_back(new BoardSegment(SegmentState::ShipPlacement));
         }
        if (std::getline(ss, tempFileInput, ';') && tempFileInput == "w")  {
            initSegments.push_back(new BoardSegment(SegmentState::Water));
        }
        if (std::getline(ss, tempFileInput, ';') && tempFileInput == "h")  {
            initSegments.push_back(new BoardSegment(SegmentState::WaterHit));
        }     
    }
    board2->init(initSegments, startingShipsPlayer);

    board1->init(grid, nullptr);

}
*/

void GameLogic::initShipConf() {
    
    //shipConf1
    shipConf1Player = {new Ship("Schlachtschiff",5,false)};
    shipConf1Computer = {new Ship("Schlachtschiff",5,false)};
}