#include "Headerdateien\GameRessources.h"

#include <iostream>
#include <iomanip>

void GameRessources::printWelcome()  {
    std::cout << R"(
         __          __ _  _  _  _                                                   _            _ 
         \ \        / /(_)| || || |                                                 | |          (_)
          \ \  /\  / /  _ | || || | __ ___   _ __ ___   _ __ ___    ___  _ __       | |__    ___  _ 
           \ \/  \/ /  | || || || |/ // _ \ | '_ ` _ \ | '_ ` _ \  / _ \| '_ \      | '_ \  / _ \| |
            \  /\  /   | || || ||   <| (_) || | | | | || | | | | ||  __/| | | |     | |_) ||  __/| |
             \/  \/    |_||_||_||_|\_\\___/ |_| |_| |_||_| |_| |_| \___||_| |_|     |_.__/  \___||_|  

         _____        _      _   __   __                                           _                
        / ____|      | |    (_) / _| / _|                                         | |               
       | (___    ___ | |__   _ | |_ | |_  ___ __   __ ___  _ __  ___   ___  _ __  | | __ ___  _ __  
        \___ \  / __|| '_ \ | ||  _||  _|/ _ \\ \ / // _ \| '__|/ __| / _ \| '_ \ | |/ // _ \| '_ \ 
        ____) || (__ | | | || || |  | | |  __/ \ V /|  __/| |   \__ \|  __/| | | ||   <|  __/| | | |
       |_____/  \___||_| |_||_||_|  |_|  \___|  \_/  \___||_|   |___/ \___||_| |_||_|\_\\___||_| |_|
    )" << std::endl;
}

void GameRessources::printWin()  {
    std::cout << R"(
         _____  _         _             _                  
        / ____|(_)       | |           | |                 
       | (___   _   ___  | |__    __ _ | |__    ___  _ __  
        \___ \ | | / _ \ | '_ \  / _` || '_ \  / _ \| '_ \ 
        ____) || ||  __/ | | | || (_| || |_) ||  __/| | | |
       |_____/ |_| \___| |_| |_| \__,_||_.__/  \___||_| |_|

          __ _   ___ __      __ ___   _ __   _ __    ___  _ __  
         / _` | / _ \\ \ /\ / // _ \ | '_ \ | '_ \  / _ \| '_ \ 
        | (_| ||  __/ \ V  V /| (_) || | | || | | ||  __/| | | |
         \__, | \___|  \_/\_/  \___/ |_| |_||_| |_| \___||_| |_|
          __/ |                                                 
         |___/                                                                                                                                                                                 
    )" << std::endl;
}

void GameRessources::printLose()  {
    std::cout << R"(
         _____  _         _             _                  
        / ____|(_)       | |           | |                 
       | (___   _   ___  | |__    __ _ | |__    ___  _ __  
        \___ \ | | / _ \ | '_ \  / _` || '_ \  / _ \| '_ \ 
        ____) || ||  __/ | | | || (_| || |_) ||  __/| | | |
       |_____/ |_| \___| |_| |_| \__,_||_.__/  \___||_| |_|

                           _                          
                          | |                         
        __   __ ___  _ __ | |  ___   _ __  ___  _ __  
        \ \ / // _ \| '__|| | / _ \ | '__|/ _ \| '_ \ 
         \ V /|  __/| |   | || (_) || |  |  __/| | | |
          \_/  \___||_|   |_| \___/ |_|   \___||_| |_|                                                                                                                                 
    )" << std::endl;

}

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

void printError(std::string textMessage, std::string type)
{
    std::string color;
    if (type == "Error")
    {
        color = RED;
    }
    else
    {
        color = GREEN;
    }

    const int boxWidth = 30;
    std::cout << color << std::string(boxWidth - 1, '-') << RESET << std::endl;
    int length = type.length();
    int freeBefore = (boxWidth - length) / 2;
    int freeAfter = boxWidth - length - freeBefore;
    std::cout << color << "| " << std::string(freeBefore - 2, ' ') << type << std::string(freeAfter - 2, ' ') << " |" << RESET << std::endl;


    size_t start = 0;
    while (start < textMessage.length())
    {
        std::string line = textMessage.substr(start, boxWidth - 4);
        std::cout << color << "| " << line << std::string(boxWidth - 4 - line.length(), ' ') << " |" << RESET << std::endl;
        start += boxWidth - 4;
    }
    std::cout << color << std::string(boxWidth - 1, '-') << RESET << std::endl;
}