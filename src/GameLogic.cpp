#include "../include/GameLogic.h"

int Player::nextID = 0;

//Initialize a player
Player::Player(std::string name) : name(name) {
    playerID = this->nextID;
    this->nextID++;
}

GameLogic::GameLogic() {}

//Menue to choose between New Game, Load Game and Settings
void GameLogic::init() { 
    Output::printWelcome();
    sigObj=this;
    std::signal(SIGINT,signal_handler);
    int inputMenu;
    loadAutosafe();
    std::vector<std::string> menuePoints {"New Game", "Load Game", "Settings", "Exit"};
    while(1) {
        initShipConf();
        Output::printMenue(menuePoints);
        inputMenu = Input::userinputInt("Bitte w\204hlen sie einen Men\201 Punkt aus: ", 1, menuePoints.size());
        switch (inputMenu) {
            case 1: //New Game 
                newGame();
                break;
            case 2: //Load Game
                loadGame();
                break;
            case 3:
                settings();
                break;
            case 4:
                exit(1);
                break;
            default:
                break;
        }
    }
}

//Start a game
void GameLogic::startGame(){
    //If your not loading a saved game gamePhase is false and ships get placed
    if(!gamePhase){
        board1->placeShips();
        std::cout << "Computer platziert seine Schiffe" << std::endl;
        board2->placeShips();
        gamePhase = true;
    }
    //Print both boards
    Output::printBothBoards(board1, board2);
    //Choose who starts to play
    int zufallAnfang = getRandomNumber(0,1);
    if (zufallAnfang == 0)  {
        Output::printBoxMessage("Sie d\201rfen anfangen!", true);
    } else  {
        Output::printBoxMessage("Der Computer f\204ngt an!", true);
    }
    int save = 10;
    //While not all ships are sunken both player attack the other board
    while(!(board1->allShipsSunk() || board2->allShipsSunk())){
        //SaveGame possible at the start and every 5 Attacks
        if (save == 5)  {
            int saveGame = Input::userinputInt("M\224chten sie das Spiel Speichern (0:Ja, 1:Nein)", 0, 1);
            if (saveGame == 0)  {
                Output::printBoxMessage("Mit welchem Namen soll das Spiel gespeichert werden.", true);
                std::cin >> gameName;
                this->saveGame();
                saveGame = Input::userinputInt("M\224chten sie das Spiel nun abbrechen? (0:Ja, 1:Nein)", 0, 1);
                if (saveGame == 0)  {
                    exit(1);
                }
            } 
            save = 0;  
        } else  {
            save++;
        }

        
        if (zufallAnfang == 0)  {
            board1->attack(board2);
            board2->attack(board1);
        } else  {
            board2->attack(board1);
            board1->attack(board2);
        }
        Output::printBothBoards(board1, board2);
    }
    if (board1->allShipsSunk())  {
        Output::printLose();
        delete board1;
        delete board2;
        gamePhase = false;
    } else {
        Output::printWin();
        delete board1;
        delete board2;
        gamePhase = false;
    }
}
    

void GameLogic::newGame() {
    //Create Ships based on a pattern
    std::vector<Ship*> startingShipsPlayer;
    std::vector<Ship*> startingShipsComputer;
    switch (shipConfigChoice)  {
    case 1:
        startingShipsPlayer = shipConf1Player;
        startingShipsComputer = shipConf1Computer;
        break;
    case 2:
        startingShipsPlayer = shipConf2Player;
        startingShipsComputer = shipConf2Computer;
        break;
    case 3:
        startingShipsPlayer = shipConf3Player;
        startingShipsComputer = shipConf3Computer;
        break;
    default:
        break;
    }
    //Ask the user for his name
    Output::printBoxMessage("Geben Sie ihren Namen ein", true);
    std::string playerName;
    std::cin >> playerName;
    gameName = "AUTOSAFE";

    //gameMode == 1 is the gamemode Player vs Computer
    if (gameMode == 1)  {
        player1 = new Player(playerName);
        player2 = new Player("Computer");
        //Create two boards
        board1 = new PlayerBoard();
        board2 = new ComputerBoard();
    } else  {
        player1 = new Player("Computer1");
        player2 = new Player("Computer2");
        //Create two boards
        board1 = new ComputerBoard();
        board2 = new ComputerBoard();
    }

    //Create a vector of BoardSegmentscl
    std::vector<BoardSegment*> initSegments;
    board1->init(initSegments,startingShipsPlayer, false);
    board2->init(initSegments, startingShipsComputer, false);
    gamePhase = false;
    startGame();
}

//Save the game 
void GameLogic::saveGame()  {
    //Create a string to save the data
    gameName;
    std::vector<Ship*> ships;
    std::string gamePhaseValue;

    //Add Playname, Playername and Phase to the String
    ships = board1->getShipsOnBoard();
    if (gamePhase == false)  {
        gamePhaseValue = "0";
    } else  {
        gamePhaseValue = "1";
    }
    
    std::string saveString = gameName + ";" + player1->name + ";" + gamePhaseValue + ";";
    
    //Add the ship config, which consists of the shipnumber + a value to decide if its sunk or not for the Playerships
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

    //Add a value to decide if its sunk or not for the Computerships
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

    //Add the States of each BoardSegment to the String for the Playerboard
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
                shipID = std::to_string(boardsegmentP->getShipOnSegment()->getId());
                boardStringPlayer = boardStringPlayer + symbol + ";" + shipID + ";";
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

    //Add the States of each BoardSegment to the String for the Computerboard
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
                shipID = std::to_string(boardsegmentC->getShipOnSegment()->getId());
                boardStringComputer = boardStringComputer + symbol + ";" + shipID + ";";
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

    saveString = saveString + boardStringComputer;

    std::ofstream csvFile("../FieldSave.csv", std::ios_base::app);

    if (csvFile.is_open())  {
        csvFile << saveString << std::endl;
        csvFile.close();
    } else  {
        Output::printBoxError("FieldSave Datei konnte nicht ge\224ffnet werden!", true);
    }   
}

//Load a existing Game
void GameLogic::loadGame() {
    std::ifstream csvFileName(SAFEFILE);
    std::vector<std::string> gameNames;

    //Read the first word of each line to get the Playname
    if (csvFileName.is_open()) {
        std::string lineN;

        while (std::getline(csvFileName, lineN)) {
            std::stringstream ss(lineN);
            
            if (std::getline(ss, gameName, ';')) {
                gameNames.push_back(gameName);
            }
        }
        csvFileName.close();
    } else  {
        Output::printBoxError("FieldSave Datei konnte nicht ge\224ffnet werden!", true);
    }

    if (gameNames.empty())  {
        std::cout << "Es gibt keine Spielst\204nde zum laden!" << std::endl;
        return;
    }
    
    //Let the user choose which play he wants to load
    int game;
    std::ifstream csvFile(SAFEFILE);
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
    } else  {
        Output::printBoxError("FieldSave Datei konnte nicht ge\224ffnet werden!", true);
    }

    //Load Playname, playername and phase
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

    //Produce based on the shipnumber ships with a pattern
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

    //Set ships to sunken or not
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

    //Set all States of the BoardSegments of the Playerboard
    std::getline(ss, tempFileInput, ';');
    int boardSize = std::stoi(tempFileInput);
    std::vector<BoardSegment*> initSegmentsPlayer;
    for(int i = 0; i < (board1->getBoardSize() * board1->getBoardSize()); i++) {
        std::getline(ss, tempFileInput, ';');
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
    //Initialize the board
    board1->init(initSegmentsPlayer, startingShipsPlayer, gamePhase);
    std::vector<BoardSegment*> initSegmentsComputer;
    
    //Set all States of the BoardSegments of the Computerboard
    for(int i = 0; i < (board2->getBoardSize() * board2->getBoardSize()); i++) {
        std::getline(ss, tempFileInput, ';');
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
    //Initialize the board
    board2->init(initSegmentsComputer, startingshipsComputer, gamePhase);
    //Start the game
    startGame();
}

//Initialize Patterns to create ships
void GameLogic::initShipConf() {

    shipConf1Player = {
        new Ship("Schlachtschiff",5,false, 1),
        new Ship("Kreuzer1",4,false, 2),
        new Ship("Kreuzer2",4,false, 3),
        new Ship("Zerst\224rer1",3,false, 4),
        new Ship("Zerst\224rer2",3,false, 5),
        new Ship("Zerst\224rer3",3,false, 6),
        new Ship("U-Boot1",2,false, 7),
        new Ship("U-Boot2",2,false, 8),
        new Ship("U-Boot3",2,false, 9),
        new Ship("U-Boot4",2,false, 10)};

    shipConf1Computer = {
        new Ship("Schlachtschiff",5,false, 1),
        new Ship("Kreuzer1",4,false, 2),
        new Ship("Kreuzer2",4,false, 3),
        new Ship("Zerst\224rer1",3,false, 4),
        new Ship("Zerst\224rer2",3,false, 5),
        new Ship("Zerst\224rer3",3,false, 6),
        new Ship("U-Boot1",2,false, 7),
        new Ship("U-Boot2",2,false, 8),
        new Ship("U-Boot3",2,false, 9),
        new Ship("U-Boot4",2,false, 10)};

    shipConf2Player = {
        new Ship("Schlachtschiff",5,false, 1),
        new Ship("Kreuzer",4,false, 2),
        new Ship("Zerst\224rer",3,false, 3),
        new Ship("U-Boot1",2,false, 4),
        new Ship("U-Boot2",2,false, 5)};

    shipConf2Computer = {
        new Ship("Schlachtschiff",5,false, 1),
        new Ship("Kreuzer",4,false, 2),
        new Ship("Zerst\224rer",3,false, 3),
        new Ship("U-Boot1",2,false, 4),
        new Ship("U-Boot2",2,false, 5)};
    
    shipConf3Player = {
        new Ship("Schlachtschiff",5,false, 1),
        new Ship("U-Boot",2,false, 2)};

    shipConf3Computer = {
        new Ship("Schlachtschiff",5,false, 1),
        new Ship("U-Boot",2,false, 2)};
}

void signal_handler(int signal) {
    GameLogic::sigObj->saveGame();
}

//Load the Autosafe if available
void GameLogic::loadAutosafe()  {
    std::ifstream csvFile(SAFEFILE);
    std::string line;
    std::vector<std::string> rightLines;
    bool autosafeAvailable = false;
    if (csvFile.is_open()) {
        while (std::getline(csvFile, line)) {
            if (line.find("AUTOSAFE") != std::string::npos)  {
                autosafeAvailable = true;
                Output::printBoxMessage("Ihr letztes Spiel wurde abgebrochen.", true);
                int choice = Input::userinputInt("Wollen sie ihr letztes Spiel laden (0:Ja 1:Nein)", 0, 1);
                if (choice == 0)  {
                    break;
                } else  {
                    deleteAutosafe();
                    return;
                }
            } else  {
                return;
            }
        }
        csvFile.close();
        if (autosafeAvailable == true)  {
            std::stringstream ss(line);
            std::string tempFileInput;
            bool tempPhase;

            std::getline(ss, GameLogic::gameName, ';');

            std::getline(ss, tempFileInput, ';');
            player1 = new Player(tempFileInput);
            player2 = new Player("Computer");


            std::getline(ss, tempFileInput, ';');
            if (tempFileInput == "1")  {
            gamePhase = true;
            } else  {
            gamePhase = false;
            }

            //Produce based on the shipnumber ships with a pattern
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

            //Set ships to sunken or not
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

            //Set all States of the BoardSegments of the Playerboard
            std::getline(ss, tempFileInput, ';');
            int boardSize = std::stoi(tempFileInput);
            std::vector<BoardSegment*> initSegmentsPlayer;
            for(int i = 0; i < (board1->getBoardSize() * board1->getBoardSize()); i++) {
                std::getline(ss, tempFileInput, ';');
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
            //Initialize the board
            board1->init(initSegmentsPlayer, startingShipsPlayer, gamePhase);
            std::vector<BoardSegment*> initSegmentsComputer;
            
            //Set all States of the BoardSegments of the Computerboard
            for(int i = 0; i < (board2->getBoardSize() * board2->getBoardSize()); i++) {
                std::getline(ss, tempFileInput, ';');
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
            //Initialize the board
            board2->init(initSegmentsComputer, startingshipsComputer, gamePhase);
            //Start the game
            startGame();
        } else  {
            Output::printBoxError("Ihre FieldSave Methode wurde nicht gefunden!", true);
        }
    }  
}

//Delete the Autosafe
void GameLogic::deleteAutosafe()  {
    std::ifstream csvFile(SAFEFILE);
    std::string line;
    std::vector<std::string> rightLines;
    if (csvFile.is_open()) {
        while (std::getline(csvFile, line)) {
            if (line.find("AUTOSAFE") == std::string::npos) {
                rightLines.push_back(line);
            }
        }
        csvFile.close();
        std::ofstream outputFile(SAFEFILE);
        if (outputFile.is_open()) {
            for (int i = 0; i < rightLines.size(); i++)  {
                outputFile << rightLines.at(i) << '\n';
            }
            outputFile.close();
        } else {
            Output::printBoxError("Ihre FieldSave Datei wurde nicht gefunden!", true);
        }

    } else  {
        Output::printBoxError("Ihre FieldSave Datei wurde nicht gefunden!", true);
    }
}

//Chooce between 3 ShipConfigs and 2 GameModes
void GameLogic::settings()  {
    std::vector<std::string> settings {"Shipconfig w\204hlen", "Spielmodus w\204hlen"};
    Output::printMenue(settings);
    int settingsChoice = Input::userinputInt("Bitte w\204hlen sie einen Men\201 Punkt aus: ", 1, settings.size());
    if (settingsChoice == 1)  {
        std::vector<std::string> shipconfigs {"10 Schiffe", "5 Schiffe", "2 Schiffe"};
        shipConfigChoice = Input::userinputInt("Bitte w\204hlen sie einen Men\201 Punkt aus: ", 1, shipconfigs.size());
    }
    if (settingsChoice == 2)  {
        std::vector<std::string> gameModes {"Player vs Computer", "Computer vs Computer"};
        gameMode = Input::userinputInt("Bitte w\204hlen sie einen Men\201 Punkt aus: ", 1, gameModes.size());
    }
    
}
//Get a random number
int GameLogic::getRandomNumber(int lowerBound, int upperBound){
    std::random_device randomNummerGen;
    std::mt19937 gen(randomNummerGen());
    std::uniform_int_distribution<int> distrubution(lowerBound,upperBound);

    return distrubution(gen);
}


