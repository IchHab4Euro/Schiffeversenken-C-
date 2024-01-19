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
    initShipConf();
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
                //loadGame();
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
        //saveGame();
    }

    Output::printPlayerBoard(board1);
    Output::printPlayerBoard(board2);


    while(!(board1->allShipsSunk())){
        std::cout << "Test" << std::endl;
        board1->attack(board2);
        //board2->attack(board1);

        Output::printPlayerBoard(board2);

        //Output::printBothBoards(board1, board2);
    }
    
}
    

void GameLogic::newGame() {
    std::vector<Ship*> startingShipsPlayer = shipConf3Player;
    std::vector<Ship*> startingShipsComputer = shipConf3Computer;
    //Todo: Spielernamen abfragen
    player1 = new Player("Rumpelstielschen");
    player2 = new Player("Computer");

    std::vector<BoardSegment*> initSegments;

    board1 = new ComputerBoard();
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

/*

void GameLogic::saveGame()  {
    std::string playName;
    std::vector<Ship*> ships;
    std::cout << "Bitte gebe einen Spielname ein: " << std::endl;
    std::cin >> playName;
    std::string gamePhaseValue;

    //String: Spielname;Spielername;Phase
    //Wenn Schiffe nicht geplaced 0 wenn geplaced 1
    ships = board1->getShipsOnBoard();
    if (gamePhase == false)  {
        gamePhaseValue = "0";
    } else  {
        gamePhaseValue = "1";
    }
    
    std::string saveString = playName + ";" + player1->name + ";" + gamePhaseValue + ";";
    
    //Shipconfig: Schiffsanzahl;S1Sunken;S2Sunken,S3Sunken
    std::string shipconfig;
    shipconfig = std::to_string(ships.size()) + ";";

    for (int i = 0; i < ships.size(); i++)  {
        std::string sunken;
        if (ships.at(i)->isSunken())  {
            sunken = "1";
        } else  {
            sunken = "0";
        }
        shipconfig = shipconfig + sunken + ";"; //sunk == 1 wenn gesunken
    }

    //ComputerString
    ships = board2->getShipsOnBoard();

    for (int i = 0; i < ships.size(); i++)  {
        std::string sunken;
        if (ships.at(i)->isSunken())  {
            sunken = "1";
        } else  {
            sunken = "0";
        }
        shipconfig = shipconfig + sunken + ";"; //sunk == 1 wenn gesunken
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
                boardStringPlayer = boardStringPlayer + symbol + ";" + shipID + ";";
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
                boardStringComputer = boardStringComputer + symbol + ";" + shipID + ";";
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
    if (shipConf1Player.size() == shipNumber)  {
        startingShipsPlayer = shipConf1Player;
        startingshipsComputer = shipConf1Computer;
    }
    if (shipConf2Player.size() == shipNumber)  {
        startingShipsPlayer = shipConf2Player;
        startingshipsComputer = shipConf2Computer;
    }
    if (shipConf3Player.size() == shipNumber)  {
        startingShipsPlayer = shipConf3Player;
        startingshipsComputer = shipConf3Computer;
    }

    for (int i = 0; i < startingShipsPlayer.size(); i++)  {
        std::getline(ss, tempFileInput, ';');
        if (tempFileInput == "1")  {
            startingShipsPlayer.at(i)->sunk = true;
        } else  {
            startingShipsPlayer.at(i)->sunk = false;
        }
    }
    for (int i = 0; i < startingshipsComputer.size(); i++)  {
        std::getline(ss, tempFileInput, ';');
        if (tempFileInput == "1")  {
            startingshipsComputer.at(i)->sunk = true;
        } else  {
            startingshipsComputer.at(i)->sunk = false;
        }
    }
    
    board1 = new PlayerBoard();
    board2 = new ComputerBoard();

    std::getline(ss, tempFileInput, ';');
    int boardSize = std::stoi(tempFileInput);
    std::vector<BoardSegment*> initSegmentsPlayer;
    std::cout << "Player" << std::endl;
    for(int i = 0; i < (board1->getBoardSize() * board1->getBoardSize()); i++) {
        std::getline(ss, tempFileInput, ';');
        std::cout << tempFileInput;
        if (tempFileInput == "r")  {
            initSegmentsPlayer.push_back(new BoardSegment(SegmentState::Revealed));
        }
        if (tempFileInput == "s")  {
            BoardSegment* boardsegment = new BoardSegment(SegmentState::Ship);
            std::string idString;
            std::getline(ss, idString, ';');
            int id = std::stoi(idString);
            boardsegment->setShipOnSegment(startingShipsPlayer[id]);
            initSegmentsPlayer.push_back(boardsegment);
        }
        if (tempFileInput == "#")  {
            BoardSegment* boardsegment = new BoardSegment(SegmentState::ShipHit);
            std::string idString;
            std::getline(ss, idString, ';');
            int id = std::stoi(idString);
            boardsegment->setShipOnSegment(startingShipsPlayer[id]);
            initSegmentsPlayer.push_back(boardsegment);
        }
        if (tempFileInput == "p")  {
            initSegmentsPlayer.push_back(new BoardSegment(SegmentState::ShipPlacement));
         }
        if (tempFileInput == "w")  {
            initSegmentsPlayer.push_back(new BoardSegment(SegmentState::Water));
        }
        if (tempFileInput == "h")  {
            initSegmentsPlayer.push_back(new BoardSegment(SegmentState::WaterHit));
        }     
    }
    std::cout << std::endl;
    board1->init(initSegmentsPlayer, startingShipsPlayer);
    std::vector<BoardSegment*> initSegmentsComputer;
    
    std::cout << "Computer" << std::endl;
    for(int i = 0; i < (board2->getBoardSize() * board2->getBoardSize()); i++) {
        std::getline(ss, tempFileInput, ';');
        std::cout << tempFileInput;
        if (tempFileInput == "r")  {
            initSegmentsComputer.push_back(new BoardSegment(SegmentState::Revealed));
        }
        if (tempFileInput == "s")  {
            BoardSegment* boardsegment = new BoardSegment(SegmentState::Ship);
            std::string idString;
            std::getline(ss, idString, ';');
            int id = std::stoi(idString);
            boardsegment->setShipOnSegment(startingshipsComputer[id]);
            initSegmentsComputer.push_back(boardsegment);
        }
        if (tempFileInput == "#")  {
            BoardSegment* boardsegment = new BoardSegment(SegmentState::ShipHit);
            std::string idString;
            std::getline(ss, idString, ';');
            int id = std::stoi(idString);
            boardsegment->setShipOnSegment(startingshipsComputer[id]);
            initSegmentsComputer.push_back(boardsegment);
        }
        if (tempFileInput == "p")  {
            initSegmentsComputer.push_back(new BoardSegment(SegmentState::ShipPlacement));
        }
        if (tempFileInput == "w")  {
            initSegmentsComputer.push_back(new BoardSegment(SegmentState::Water));
        }
        if (tempFileInput == "h")  {
            initSegmentsComputer.push_back(new BoardSegment(SegmentState::WaterHit));
        }     
    }

    board2->init(initSegmentsComputer, startingshipsComputer);

    startGame();
}


void GameLogic::initShipConf() {

    shipConf1Player = {
        new Ship("Schlachtschiff",5,false, 1),
        new Ship("Kreuzer1",4,false, 2),
        new Ship("Kreuzer2",4,false, 3),
        new Ship("Zerstörer1",3,false, 4),
        new Ship("Zerstörer2",3,false, 5),
        new Ship("Zerstörer3",3,false, 6),
        new Ship("U-Boot1",2,false, 7),
        new Ship("U-Boot2",2,false, 8),
        new Ship("U-Boot3",2,false, 9),
        new Ship("U-Boot4",2,false, 10)};

    shipConf1Computer = {
        new Ship("Schlachtschiff",5,false, 1),
        new Ship("Kreuzer1",4,false, 2),
        new Ship("Kreuzer2",4,false, 3),
        new Ship("Zerstörer1",3,false, 4),
        new Ship("Zerstörer2",3,false, 5),
        new Ship("Zerstörer3",3,false, 6),
        new Ship("U-Boot1",2,false, 7),
        new Ship("U-Boot2",2,false, 8),
        new Ship("U-Boot3",2,false, 9),
        new Ship("U-Boot4",2,false, 10)};

    shipConf2Player = {
        new Ship("Schlachtschiff",5,false, 1),
        new Ship("Kreuzer",4,false, 2),
        new Ship("Zerstörer",3,false, 3),
        new Ship("U-Boot1",2,false, 4),
        new Ship("U-Boot2",2,false, 5)};

    shipConf2Computer = {
        new Ship("Schlachtschiff",5,false, 1),
        new Ship("Kreuzer",4,false, 2),
        new Ship("Zerstörer",3,false, 3),
        new Ship("U-Boot1",2,false, 4),
        new Ship("U-Boot2",2,false, 5)};
    
    shipConf3Player = {
        new Ship("Schlachtschiff",5,false, 1),
        new Ship("U-Boot",2,false, 2)};

    shipConf3Computer = {
        new Ship("Schlachtschiff",5,false, 1),
        new Ship("U-Boot",2,false, 2)};
}