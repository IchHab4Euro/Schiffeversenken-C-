#include "../include/GameRessources.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <cctype>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

void GameRessources::printWelcome()  {
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

void GameRessources::printWin()  {
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

void GameRessources::printLose()  {
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

void GameRessources::printBoxMessage(std::string textMessage, std::string type)
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

int GameRessources::printMenue()  {
    const int menueboxWidth = boxWidth;

    std::cout << std::string(menueboxWidth, '-') << std::endl;
    int length = 5;
    int freeBefore = (menueboxWidth - length) / 2;
    int freeAfter = menueboxWidth - length - freeBefore;
    std::cout << "| " << std::string(freeBefore - 2, ' ') << "Menue" << std::string(freeAfter - 2, ' ') << " |" << std::endl;

    std::vector<std::string> menuePoints;
    menuePoints.push_back("1. Spiel starten");
    menuePoints.push_back("2. Tutorial");
    menuePoints.push_back("3. Profil");
    menuePoints.push_back("4. Statistiken");
    menuePoints.push_back("5. Programm beenden");

    length = 0;
    for (int i = 0; i < menuePoints.size(); i++)  {
        if (menuePoints.at(i).size() > length)  {
            length = menuePoints.at(i).size();
        }
    }

    freeBefore = (menueboxWidth - length) / 2;
    
    for (int i = 0; i < menuePoints.size(); i++)
    {
        std::cout << "| " << std::string(freeBefore - 2, ' ') << menuePoints.at(i) << std::string(boxWidth - freeBefore - 2 - menuePoints.at(i).size(), ' ') << " |" << std::endl;
    }

    std::cout << std::string(menueboxWidth, '-') << std::endl;
    
    int selection;
    std::cout << "Bitte waehlen sie einen Menue Punkt aus" << std::endl;
    std::cin >> selection;
    return selection;
}

int GameRessources::userinputInt(std::string pMessage, int pLower, int pUpper)  {
    int inputCor = 1;
    int input;
    while (inputCor != 0)
    {
        std::cout << pMessage << std::endl;
        //Kontrolliert ob die Eingabe eine Zahl ist
        while (!(std::cin >> input))  {
            std::cout << "Bitte geben sie eine Zahl ein!" << std::endl;
            std::cin.clear();               //Fehlerstatus von cin wird zurückgesetzt
            std::cin.ignore(1000, '\n');    //Ersten 1000 Zeichen werden ignoriert; Alle Zeichen bis zu einem Enter werden überlesen
        }
        if (input >= pLower && input <= pUpper)
        {
            inputCor = 0;
        } else  {
            pMessage = "Bitte geben sie eine g\201ltige Zahl ein!";
        }
    }
    return input;
}

std::string GameRessources::userinputString(std::string pMessage)  {
    std::cout << pMessage << std::endl;
}

std::string GameRessources::userinputCoordinates(std::string pMessage, int pBoardSize)  {
    std::string message = pMessage;
    std::string input;
    char letter;
    int numberI;
    int inputKorrekt = 1;
    char upperLetter = 'A' + pBoardSize -1;

    std::string numberSizeString = std::to_string(pBoardSize);
    int numberSizeInt = numberSizeString.length();

    while (inputKorrekt == 1)  {
        std::cout << message << std::endl;
        std::cin >> input;

        if (!(input.size() > 1 && input.size() <= 1 + numberSizeInt))  {
            std::cout << "Ihre Eingabe muss zwischen 1 und " << 1 + numberSizeInt << " Zeichen lange sein!" << std::endl;
            message = "Bitte geben sie eine g\201ltige Koordinate ein.";
            continue;
        }
        

        letter = input[0];
        if (!(std::isalpha(letter)))  {
            std::cout << "Das erste Zeichen muss ein Buchstabe sein!" << std::endl;
            message = "Bitte geben sie eine g\201ltige Koordinate ein.";
            continue;
        }
        if (std::islower(letter))  {
            letter = std::toupper(letter);
        }
        

        std::string numberS = input.substr(1, numberSizeInt);
        int intCor = 0;
        for (int i = 0; i < numberS.length(); i++)  {
            if (!(isdigit(numberS.at(i))))  {
                std::cout << "Ihre Koordinate darf an Stelle " << i + 2 << " keinen Buchstaben enthalten!"<< std::endl;
                intCor = 1;
                break;
            }
        }
        if (intCor == 0)  {
            numberI = std::stoi(numberS);
        } else {
            message = "Bitte geben sie eine g\201ltige Koordinate ein.";
            continue;
        }

        if (!(letter >= 'A' && letter <= upperLetter))  {
            std::cout << "Bitte geben sie einen Buchstaben von A bis " << upperLetter << " ein!" << std::endl;
            message = "Bitte geben sie eine g\201ltige Koordinate ein.";
            continue;
        }
        if (!(numberI >= 1 && numberI <= pBoardSize))  {
            std::cout << "Die Zahl ihrer Koordinate liegt nicht zwischen 1 und " << pBoardSize << "!" << std::endl;
            message = "Bitte geben sie eine g\201ltige Koordinate ein.";
            continue;
        }
        inputKorrekt = 0;
    }
    input = letter + std::to_string(numberI);
    std::cout << input << std::endl;
    return input;
}