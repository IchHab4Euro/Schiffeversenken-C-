#include "../include/Output.h"

Output::Output(){};

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

    freeBefore = (menueboxWidth - length -4) / 2;
    
    for (int i = 0; i < pMenuePoints.size(); i++)
    {
        std::cout << "| " << std::string(freeBefore - 2, ' ') << i+1 << "." << pMenuePoints.at(i) << std::string(boxWidth - freeBefore - 4 - pMenuePoints.at(i).size(), ' ') << " |" << std::endl;
    }

    std::cout << std::string(menueboxWidth, '-') << std::endl;
    
    int selection;
    std::cout << "Bitte waehlen sie einen Menue Punkt aus: " << std::endl;
}

void Output::printBoxError(std::string errorMessage)  {
    std::string color;
    color = RED;

    const int textboxWidth = boxWidth;
    std::string type = "Error";

    std::cout << color << std::string(textboxWidth, '-') << RESET << std::endl;
    int length = type.length();
    int freeBefore = (textboxWidth - length) / 2;
    int freeAfter = textboxWidth - length - freeBefore;
    std::cout << color << "| " << std::string(freeBefore - 2, ' ') << type << std::string(freeAfter - 2, ' ') << " |" << RESET << std::endl;


    size_t start = 0;
    while (start < errorMessage.length())
    {
        std::string line = errorMessage.substr(start, textboxWidth - 5);
        std::string connection;
        if (line.length() == textboxWidth-5)  {
            connection = "-";
        } else  {
            connection = std::string(textboxWidth - 4 - line.length(), ' ');
        }
        
        std::cout << color << "| " << line << connection << " |" << RESET << std::endl;
        start += textboxWidth - 5;
    }
    std::cout << color << std::string(textboxWidth, '-') << RESET << std::endl;
}

void Output::printBoxMessage(std::string textMessage)  {
    std::string color;
    color = GREEN;

    const int textboxWidth = boxWidth;
    std::string type = "Nachricht";

    std::cout << color << std::string(textboxWidth, '-') << RESET << std::endl;
    int length = type.length();
    int freeBefore = (textboxWidth - length) / 2;
    int freeAfter = textboxWidth - length - freeBefore;
    std::cout << color << "| " << std::string(freeBefore - 2, ' ') << type << std::string(freeAfter - 2, ' ') << " |" << RESET << std::endl;


    size_t start = 0;
    while (start < textMessage.length())
    {
        std::string line = textMessage.substr(start, textboxWidth - 5);
        std::string connection;
        if (line.length() == textboxWidth-5)  {
            connection = "-";
        } else  {
            connection = std::string(textboxWidth - 4 - line.length(), ' ');
        }
        
        std::cout << color << "| " << line << connection << " |" << RESET << std::endl;
        start += textboxWidth - 5;
    }
    std::cout << color << std::string(textboxWidth, '-') << RESET << std::endl;
}

void Output::printPlayerBoard(Board* pBoard)  {
    int boardSize = pBoard->getBoardSize();
    std::cout << std::string(7, ' ');
    for (int i = 0; i < boardSize; i++)  {
        std::cout << std::string(4, ' ') << i+1 << std::string(3, ' ');
    }

    std::cout << std::endl;
    std::cout << std::string(7, ' ');
    for (int i = 1; i <= boardSize; i++)
    {
        std::cout << std::string(8, '-');
    }
    std::cout << "-" << std::endl;

    for (int i = 0; i < boardSize; i++)
    {
        printRow(pBoard, i);
        
        std::cout << std::string(7, ' ');
        for (int i = 1; i <= boardSize; i++)  {
            std::cout << std::string(8, '-');
        }
        std::cout << "-" << std::endl;
    }
}

void Output::printRow(Board* board, int pRow)  {
    char symbol;
    char letter = 'A';
    letter = letter+pRow;
    for (int j = 0; j < 3; j++)  {
        if (j == 1)  {
            std::cout << std::string(3, ' ') << letter << std::string(3, ' ');
        } else  {
            std::cout << std::string(7, ' ');   
        }
        
        for (int i = 0; i < 10; i++)  {
            SegmentState state = board->grid[pRow][i]->fieldState;
            switch (state)  {
            case SegmentState::Water:
                symbol = ' ';
                break;
            case SegmentState::Ship:
                symbol = '#';
                break;
            default:
                symbol = ' ';
                break;
            }
            std::cout << "|" << std::string(7, symbol);
        }
        std::cout << "|" << std::endl;
    }
}

void Output::printBothBoards(Board* pBoardPlayer, Board* pBoardComputer)  {
    int boardSize = pBoardPlayer->getBoardSize();
    std::cout << std::string(7, ' ');
    for (int i = 0; i < boardSize; i++)  {
        int length = 0;
        if (i >=10)  {
            length = 1;
        } else if (i >= 100)  {
            length = 2;
        }
        std::cout << std::string(4, ' ') << i+1 << std::string(3 - length, ' ');
    }
    std::cout << std::string(9, ' ');
    for (int i = 0; i < boardSize; i++)  {
        int length = 0;
        if (i >=10)  {
            length = 1;
        } else if (i >= 100)  {
            length = 2;
        }
        std::cout << std::string(4, ' ') << i+1 << std::string(3-length, ' ');
    }
    std::cout << std::endl;

    std::cout << std::string(7, ' ');
    for (int i = 1; i <= boardSize; i++)
    {
        std::cout << std::string(8, '-');
    }
    std::cout << "-" << std::string(9, ' ');
    for (int i = 1; i <= boardSize; i++)
    {
        std::cout << std::string(8, '-');
    }
    std::cout << "-" << std::endl;

    for (int i = 0; i < 10; i++)  {
        printRowTwoBoards(pBoardPlayer, pBoardComputer, i);
        
        std::cout << std::string(7, ' ');
        for (int i = 1; i <= boardSize; i++)  {
            std::cout << std::string(8, '-');
        }
        std::cout << "-" << std::string(9, ' ');
        for (int i = 1; i <= boardSize; i++)  {
            std::cout << std::string(8, '-');
        }
        std::cout << "-" << std::endl;
    }
    std::cout << std::string((boardSize/2)*8, ' ') << "Spielerboard" << std::string(boardSize*8-2, ' ') << "Computerboard" << std::endl;
}

void Output::printRowTwoBoards(Board* pPlayer, Board* pComputer, int pRow)  {
    for (int j = 0; j < 3; j++)  {
        char letter = 'A';
        letter = letter+pRow;
        if (j == 1)  {
            std::cout << std::string(3, ' ') << letter << std::string(3, ' ');
        } else  {
            std::cout << std::string(7, ' ');   
        }
        for (int i = 0; i < 10; i++)  {
            SegmentState stateField = pPlayer->grid[pRow][i]->fieldState;
            char symbolP;
            switch (stateField)  {
            case SegmentState::Water:
                symbolP = ' ';
                break;
            case SegmentState::Ship:
                symbolP = '#';
                break;
            default:
                symbolP = ' ';
                break;
            }
            std::cout << "|" << std::string(7, symbolP);
        }
        
        std::cout << "|" << std::string(9, ' ');
        char symbolC; 
        for (int i = 0; i < 10; i++)  {
            if (pComputer->grid[pRow][i]->isShipHit())  {                 
                symbolC = 's';
            } else  {
                symbolC = ' ';
            }
            std::cout << "|" << std::string(7, symbolC);
        }
        if (j == 1)  {
            std::cout << "|" << std::string(4, ' ') << letter << std::endl;
        } else  {
            std::cout << "|" << std::endl;  
        }

    }
}

void Output::printBoardWithMenue(Board* pBoard, std::vector<Ship*> pMenue)  {
    int boardSize = pBoard->getBoardSize();
    int menuePos = 0;
    std::cout << std::string(7, ' ');
    for (int i = 0; i < boardSize; i++)  {
        std::cout << std::string(4, ' ') << i+1 << std::string(3, ' ');
    }

    std::cout << std::endl;
    std::cout << std::string(7, ' ');

    for (int i = 1; i <= boardSize; i++)
    {
        std::cout << std::string(8, '-');
    }
    std::cout << "-" << std::string(8, ' ') << "Ihre Schiffe: " << std::endl;

    for (int i = 0; i < 10; i++)
    {
        menuePos = printRowMenue(pBoard, pMenue, i, menuePos);
        
        std::cout << std::string(7, ' ');
        for (int i = 1; i <= boardSize; i++)  {
            std::cout << std::string(8, '-');
        }
        std::cout << "-" << std::string(8, ' ') <<  printShipNameAndLength(pMenue, menuePos) << std::endl;
        menuePos++;
    }
}

int Output::printRowMenue(Board* board, std::vector<Ship*> pMenue, int pRow, int pMenuePos)  {
    char symbol;
    char letter = 'A';
    letter = letter+pRow;
    for (int j = 0; j < 3; j++)  {
        if (j == 1)  {
            std::cout << std::string(3, ' ') << letter << std::string(3, ' ');
        } else  {
            std::cout << std::string(7, ' ');   
        }
        for (int i = 0; i < 10; i++)  {
            SegmentState state = board->grid[pRow][i]->fieldState;
            switch (state)
            {
            case SegmentState::Water:
                symbol = ' ';
                break;
            case SegmentState::Ship:
                symbol = '#';
                break;
            default:
                symbol = ' ';
                break;
            }
            std::cout << "|" << std::string(7, symbol);
        }
        std::cout << "|" << std::string(8, ' ') << printShipNameAndLength(pMenue, pMenuePos) << std::endl;
        pMenuePos++;
    }
    return pMenuePos;
}

std::string Output::printShipNameAndLength(std::vector<Ship*> pMenue, int pMenuePos)  {
    if (pMenue.size() <= pMenuePos )  {
        return "";
    } else  {
        Ship* ship = pMenue[pMenuePos];
        std::string output;
        output = ship->getName() + " Size: " + std::to_string(ship->getLength());
        return output;
    }
}

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