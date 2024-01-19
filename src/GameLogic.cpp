#include "../include/GameLogic.h"

int Player::nextID = 0;

//Initialize a player
Player::Player(std::string name) : name(name) {
    playerID = this->nextID;
    this->nextID++;
}

GameLogic::GameLogic() {
}

//Menue to choose between New Game, Load Game and Settings
void GameLogic::init() { 
    initShipConf();
    Output::printWelcome(); 
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
                loadGame();
                break;
            case 3: //Exit
                //Todo: Settings
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
        board2->placeShips();
        gamePhase = true;
    }
    //Print both boards
    Output::printBothBoards(board1, board2);
    //Choose who starts to play
    int zufallAnfang = getRandomNumber(0,1);
    if (zufallAnfang == 0)  {
        Output::printBoxMessage("Sie duerfen anfangen!", true);
    } else  {
        Output::printBoxMessage("Der Computer faengt an!", true);
    }
    
    //While not all ships are sunken both player attack the other board
    while(!(board1->allShipsSunk() || board2->allShipsSunk())){
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
    }
    if (board2->allShipsSunk())  {
        Output::printWin();
    }
}
    

void GameLogic::newGame() {
    //Create Ships base on a pattern
    std::vector<Ship*> startingShipsPlayer = shipConf1Player;
    std::vector<Ship*> startingShipsComputer = shipConf1Computer;

    //Ask the user for his name
    std::cout << "Bitte geben sie ihren Namen ein: " << std::endl;
    std::string playerName;
    std::cin >> playerName;
    player1 = new Player(playerName);
    player2 = new Player("Computer");

    //Create a vector of BoardSegments
    std::vector<BoardSegment*> initSegments;

    //Create two boards
    board1 = new PlayerBoard();
    board2 = new ComputerBoard();

    //Fill the vector with BordSegments with state Water
    for(int i = 0; i < (board1->getBoardSize() * board1->getBoardSize()); i++) {
        initSegments.push_back(new BoardSegment(SegmentState::Water));
    }
    board1->init(initSegments, startingShipsPlayer, false);
    initSegments.clear();
    for(int i = 0; i < (board2->getBoardSize() * board2->getBoardSize()); i++) {
        initSegments.push_back(new BoardSegment(SegmentState::Water));
    }
    board2->init(initSegments, startingShipsComputer, false);
    gamePhase = false;
    startGame();
}

//Save the game 
void GameLogic::saveGame()  {
    //Create a string to save the data
    std::string playName;
    std::vector<Ship*> ships;
    //Ask for Playername
    std::cout << "Bitte gebe einen Spielname ein: " << std::endl;
    std::cin >> playName;
    std::string gamePhaseValue;

    //Add Playname, Playername and Phase to the String
    ships = board1->getShipsOnBoard();
    if (gamePhase == false)  {
        gamePhaseValue = "0";
    } else  {
        gamePhaseValue = "1";
    }
    
    std::string saveString = playName + ";" + player1->name + ";" + gamePhaseValue + ";";
    
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

    saveString = saveString + boardStringComputer;

    std::ofstream csvFile("../FieldSave.csv", std::ios_base::app);

    if (csvFile.is_open())  {
        csvFile << saveString << std::endl;
        csvFile.close();
    } else  {
        std::cout << "Datei konnte nicht ge\224ffnet werden!" << std::endl;
    }   
}

//Load a existing Game
void GameLogic::loadGame() {
    std::ifstream csvFileName("../FieldSave.csv");
    std::vector<std::string> gameNames;
    std::string gameName;

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
    }

    if (gameNames.empty())  {
        std::cout << "Es gibt keine Spielst\204nde zum laden!" << std::endl;
        return;
    }
    
    //Let the user choose which play he wants to load
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
    std::cout << "Player" << std::endl;
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

//Get a random number
int GameLogic::getRandomNumber(int lowerBound, int upperBound){
    std::random_device randomNummerGen;
    std::mt19937 gen(randomNummerGen());
    std::uniform_int_distribution<int> distrubution(lowerBound,upperBound);

    return distrubution(gen);
}