#include "../include/Output.h"
#include "../include/Board.h"

void  Output::printMenue(std::vector<std::string> pMenuePoints)  {
    const int menueboxWidth = boxWidth;

    std::cout << std::string(menueboxWidth, '-') << std::endl;
    int length = 5;
    int freeBefore = (menueboxWidth - length) / 2;
    int freeAfter = menueboxWidth - length - freeBefore;
    std::cout << "| " << std::string(freeBefore - 2, ' ') << "Menue" << std::string(freeAfter - 2, ' ') << " |" << std::endl;

    

    length = 0;
    for (int i = 0; i < pMenuePoints.size(); i++)  {
        if (pMenuePoints.at(i).size() > length)  {
            length = pMenuePoints.at(i).size();
        }
    }

    freeBefore = (menueboxWidth - length) / 2;
    
    for (int i = 0; i < pMenuePoints.size(); i++)
    {
        std::cout << "| " << std::string(freeBefore - 2, ' ') << pMenuePoints.at(i) << std::string(boxWidth - freeBefore - 2 - pMenuePoints.at(i).size(), ' ') << " |" << std::endl;
    }

    std::cout << std::string(menueboxWidth, '-') << std::endl;
    
    int selection;
    std::cout << "Bitte waehlen sie einen Menue Punkt aus" << std::endl;
}

void Output::printBoxMessage(std::string textMessage, std::string type)  {
    std::string color;
    if (type == "Error")
    {
        color = RED;
    }
    else
    {
        color = GREEN;
    }

    const int textboxWidth = boxWidth;

    std::cout << color << std::string(textboxWidth, '-') << RESET << std::endl;
    int length = type.length();
    int freeBefore = (textboxWidth - length) / 2;
    int freeAfter = textboxWidth - length - freeBefore;
    std::cout << color << "| " << std::string(freeBefore - 2, ' ') << type << std::string(freeAfter - 2, ' ') << " |" << RESET << std::endl;


    size_t start = 0;
    while (start < textMessage.length())
    {
        std::string line = textMessage.substr(start, textboxWidth - 4);
        std::cout << color << "| " << line << std::string(textboxWidth - 4 - line.length(), ' ') << " |" << RESET << std::endl;
        start += textboxWidth - 4;
    }
    std::cout << color << std::string(textboxWidth, '-') << RESET << std::endl;
}

void Output::printPlayerBoard(Board* pBoard)  {
    int boardSize = pBoard->getBoardSize();

    for (int i = 1; i <= boardSize; i++)
    {
        std::cout << std::string(8, '-');
    }
    std::cout << "-" << std::endl;

    for (int i = 0; i < 10; i++)
    {
        printRow(pBoard, i);
        
        for (int i = 1; i <= boardSize; i++)  {
            std::cout << std::string(8, '-');
        }
        std::cout << "-" << std::endl;
    }
}

void Output::printRow(Board* board, int pRow)  {
    char symbol;
    for (int i = 0; i < 3; i++)  {
        for (int i = 0; i < 10; i++)  {
            BoardField::FieldState state = board->grid[pRow][i].fieldState;
            switch (state)
            {
            case BoardField::FieldState::Water:
                symbol = '~';
                break;
            case BoardField::FieldState::Ship:
                symbol = 's';
                break;
            case BoardField::FieldState::ShipPlacement:
                symbol = 'p';
                break;
            default:
                break;
            }
            std::cout << "|" << std::string(7, symbol);
        }
        std::cout << "|" << std::endl;
    }
}

void Output::printBothBoards(Board* pBoardPlayer, Board* pBoardComputer)  {
    int boardSize = pBoardPlayer->getBoardSize();

    for (int i = 1; i <= boardSize; i++)
    {
        std::cout << std::string(8, '-');
    }
    std::cout << "-" << std::string(8, ' ');
    for (int i = 1; i <= boardSize; i++)
    {
        std::cout << std::string(8, '-');
    }
    std::cout << "-" << std::endl;

    for (int i = 0; i < 10; i++)  {
        printRowTwoBoards(pBoardPlayer, pBoardComputer, i);
        
        for (int i = 1; i <= boardSize; i++)  {
            std::cout << std::string(8, '-');
        }
        std::cout << "-" << std::string(8, ' ');
        for (int i = 1; i <= boardSize; i++)  {
            std::cout << std::string(8, '-');
        }
        std::cout << "-" << std::endl;
    }
}

void Output::printRowTwoBoards(Board* pPlayer, Board* pComputer, int pRow)  {
    for (int i = 0; i < 3; i++)  {
        for (int i = 0; i < 10; i++)  {
            BoardField::FieldState stateP = pPlayer->grid[pRow][i].fieldState;
            char symbol;
            switch (stateP)
            {
            case BoardField::FieldState::Water:
                symbol = '~';
                break;
            case BoardField::FieldState::Ship:
                symbol = 's';
                break;
            case BoardField::FieldState::ShipPlacement:
                symbol = 'p';
                break;
            default:
                symbol = '~';
                break;
            }
            std::cout << "|" << std::string(7, symbol);
        }
        std::cout << "|" << std::string(8, ' ');
        char symbol; 
        for (int i = 0; i < 10; i++)  {
            BoardField::FieldState stateC = pComputer->grid[pRow][i].fieldState;
            ShipSegment::ShipState stateS = pComputer->grid[pRow][i].shipSegment.shipState;
            if (stateC == BoardField::FieldState::Ship && stateS == ShipSegment::ShipState::Hit)  {                 //Überprüfen ob im grid ein getroffenes Schiff ist und gegebenfalls anzeigen
                symbol = 's';
            } else  {
                symbol = '~';
            }
            
            symbol = '~';
            std::cout << "|" << std::string(7, symbol);
        }
        std::cout << "|" << std::endl;

    }
}

void Output::printBoardWithMenue(Board* pBoard, std::vector<Ship>* pMenue)  {
    int boardSize = pBoard->getBoardSize();
    int menuePos = 0;

    for (int i = 1; i <= boardSize; i++)
    {
        std::cout << std::string(8, '-');
    }
    std::cout << "-" << std::string(8, ' ') << "Ihre Schiffe: " << std::endl;

    for (int i = 0; i < 10; i++)
    {
        menuePos = printRowMenue(pBoard, pMenue, i, menuePos);
        
        for (int i = 1; i <= boardSize; i++)  {
            std::cout << std::string(8, '-');
        }
        std::cout << "-" << std::string(8, ' ') <<  printShipNameAndLength(pMenue, menuePos) << std::endl;
        menuePos++;
    }
}

int Output::printRowMenue(Board* board, std::vector<Ship>* pMenue, int pRow, int pMenuePos)  {
    char symbol;
    for (int i = 0; i < 3; i++)  {
        for (int i = 0; i < 10; i++)  {
            BoardField::FieldState state = board->grid[pRow][i].fieldState;
            switch (state)
            {
            case BoardField::FieldState::Water:
                symbol = '~';
                break;
            case BoardField::FieldState::Ship:
                symbol = 's';
                break;
            case BoardField::FieldState::ShipPlacement:
                symbol = 'p';
                break;
            default:
                symbol = '~';
                break;
            }
            std::cout << "|" << std::string(7, symbol);
        }
        std::cout << "|" << std::string(8, ' ') << printShipNameAndLength(pMenue, pMenuePos) << std::endl;
        pMenuePos++;
    }
    return pMenuePos;
}

std::string Output::printShipNameAndLength(std::vector<Ship>* pMenue, int pMenuePos)  {
    if (pMenue->size() <= pMenuePos )  {
        return "";
    } else  {
        Ship ship = pMenue->at(pMenuePos);
        std::string output;
        output = ship.getName() + " Size: " + std::to_string(ship.getLength());
        return output;
    }
}



    /*
void Board::printBoard() const {
    for (int i = -1; i < 11; i++)
    {
        if (i == -1 || i == 0)
        {
            std::cout << " ";
        } else {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;

    char c = 'A';
    for (int i = 0; i < 10; i++)
    {
        std::cout << c << "|";
        for (int j = 0; j < 10; j++)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << "|" << std::endl;
        c++;
    }
}
*/


void Output::printWelcome()  {
    std::cout << R"(
         __          __ _  _  _  _                                                 _            _ 
         \ \        / /(_)| || || |                                               | |          (_)
          \ \  /\  / /  _ | || || | __ ___   _ __ ___   _ __ ___    ___  _ __     | |__    ___  _ 
           \ \/  \/ /  | || || || |/ // _ \ | '_ ` _ \ | '_ ` _ \  / _ \| '_ \    | '_ \  / _ \| |
            \  /\  /   | || || ||   <| (_) || | | | | || | | | | ||  __/| | | |   | |_) ||  __/| |
             \/  \/    |_||_||_||_|\_\\___/ |_| |_| |_||_| |_| |_| \___||_| |_|   |_.__/  \___||_|  

         _____        _      _   __   __                                           _                
        / ____|      | |    (_) / _| / _|                                         | |               
       | (___    ___ | |__   _ | |_ | |_  ___ __   __ ___  _ __  ___   ___  _ __  | | __ ___  _ __  
        \___ \  / __|| '_ \ | ||  _||  _|/ _ \\ \ / // _ \| '__|/ __| / _ \| '_ \ | |/ // _ \| '_ \ 
        ____) || (__ | | | || || |  | | |  __/ \ V /|  __/| |   \__ \|  __/| | | ||   <|  __/| | | |
       |_____/  \___||_| |_||_||_|  |_|  \___|  \_/  \___||_|   |___/ \___||_| |_||_|\_\\___||_| |_|
    )" << std::endl;
}

void Output::printWin()  {
    std::cout << R"(
         _____  _           _             _                  
        / ____|(_)         | |           | |                 
       | (___   _   ___    | |__    __ _ | |__    ___  _ __  
        \___ \ | | / _ \   | '_ \  / _` || '_ \  / _ \| '_ \ 
        ____) || ||  __/   | | | || (_| || |_) ||  __/| | | |
       |_____/ |_| \___|   |_| |_| \__,_||_.__/  \___||_| |_|

          __ _   ___ __      __ ___   _ __   _ __    ___  _ __  
         / _` | / _ \\ \ /\ / // _ \ | '_ \ | '_ \  / _ \| '_ \ 
        | (_| ||  __/ \ V  V /| (_) || | | || | | ||  __/| | | |
         \__, | \___|  \_/\_/  \___/ |_| |_||_| |_| \___||_| |_|
          __/ |                                                 
         |___/                                                                                                                                                                                 
    )" << std::endl;
}

void Output::printLose()  {
    std::cout << R"(
         _____  _           _             _                  
        / ____|(_)         | |           | |                 
       | (___   _   ___    | |__    __ _ | |__    ___  _ __  
        \___ \ | | / _ \   | '_ \  / _` || '_ \  / _ \| '_ \ 
        ____) || ||  __/   | | | || (_| || |_) ||  __/| | | |
       |_____/ |_| \___|   |_| |_| \__,_||_.__/  \___||_| |_|

                           _                          
                          | |                         
        __   __ ___  _ __ | |  ___   _ __  ___  _ __  
        \ \ / // _ \| '__|| | / _ \ | '__|/ _ \| '_ \ 
         \ V /|  __/| |   | || (_) || |  |  __/| | | |
          \_/  \___||_|   |_| \___/ |_|   \___||_| |_|                                                                                                                                 
    )" << std::endl;

}