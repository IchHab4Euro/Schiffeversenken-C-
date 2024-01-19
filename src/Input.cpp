#include "../include/Input.h"

std::string Input::userinputCoordinates(std::string pMessage, int pBoardSize)  {
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
    return input;
}

int Input::userinputInt(std::string pMessage, int pLower, int pUpper)  {
    int inputCor = 1;
    int input;
    while (inputCor != 0)
    {
        std::cout << pMessage << std::endl;
        //Kontrolliert ob die Eingabe eine Zahl ist
        while (!(std::cin >> input) || std::cin.peek() != '\n')  {
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