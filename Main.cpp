#include "Headerdateien/PlayerBoard.h"
#include "Headerdateien/ComputerBoard.h"
#include "Headerdateien/GameRessources.h"

#include "Headerdateien/Ship.h"

#include <iostream>

int start()  {
    GameRessources gameRessource;
    gameRessource.printWelcome();

    std::cout << "1: Spiel starten" << std::endl;
    std::cout << "2: Statistik anschauen" << std::endl;
    std::cout << "3: Programm beenden" << std::endl;
    int auswahl;
    int eingabeKorrekt = 1;

    //Es wird solange gewartet bis eine gültige Eingabe eingegeben wird
    do
    {
        std::cout << "Bitte waehlen sie eine Nummer: " << std::endl;

        //Kontrolliert ob die Eingabe eine Zahl ist
        while (!(std::cin >> auswahl))
        {
            std::cout << "Bitte geben sie eine Zahl ein!" << std::endl;
            std::cin.clear();               //Fehlerstatus von cin wird zurückgesetzt
            std::cin.ignore(1000, '\n');    //Ersten 1000 Zeichen werden ignoriert; Alle Zeichen bis zu einem Enter werden überlesen
        }
        switch (auswahl) {
        case 1:

            //Funktion noch zu integrieren

            std::cout << "Spiel starten" << std::endl;
            eingabeKorrekt = 0;
            break;
        case 2:

            //Funktion noch zu integrieren

            std::cout << "Statistiken laden" << std::endl;
            eingabeKorrekt = 0;
            break;
        case 3:
            eingabeKorrekt = 0;
            break;
        default:
            std::cout << "Ungueltige Eingabe!" << std::endl;
            break;
    }
    } while (eingabeKorrekt != 0);
    return 0;
}

int gewonnen()  {
    GameRessources gameRessource;
    gameRessource.printWin();

    std::cout << "1: Rematch" << std::endl;
    std::cout << "2: Hauptmenue" << std::endl;
    std::cout << "3: Programm beenden" << std::endl;
    int auswahl;
    int eingabeKorrekt = 1;

    //Es wird solange gewartet bis eine gültige Eingabe eingegeben wird
    do
    {
        std::cout << "Bitte waehlen sie eine Nummer: " << std::endl;

        //Kontrolliert ob die Eingabe eine Zahl ist
        while (!(std::cin >> auswahl))
        {
            std::cout << "Bitte geben sie eine Zahl ein!" << std::endl;
            std::cin.clear();               //Fehlerstatus von cin wird zurückgesetzt
            std::cin.ignore(1000, '\n');    //Ersten 1000 Zeichen werden ignoriert; Alle Zeichen bis zu einem Enter werden überlesen
        }
        switch (auswahl) {
        case 1:

            //Funktion noch zu integrieren

            std::cout << "Rematch" << std::endl;
            eingabeKorrekt = 0;
            break;
        case 2:

            //Funktion noch zu integrieren

            std::cout << "Hauptmenue" << std::endl;
            eingabeKorrekt = 0;
            break;
        case 3:
            eingabeKorrekt = 0;
            break;
        default:
            std::cout << "Ungueltige Eingabe!" << std::endl;
            break;
    }
    } while (eingabeKorrekt != 0);
    return 0;
}

int verloren()  {
    GameRessources gameRessource;
    gameRessource.printLose();

    std::cout << "1: Rematch" << std::endl;
    std::cout << "2: Hauptmenue" << std::endl;
    std::cout << "3: Programm beenden" << std::endl;
    int auswahl;
    int eingabeKorrekt = 1;

    //Es wird solange gewartet bis eine gültige Eingabe eingegeben wird
    do
    {
        std::cout << "Bitte waehlen sie eine Nummer: " << std::endl;

        //Kontrolliert ob die Eingabe eine Zahl ist
        while (!(std::cin >> auswahl))
        {
            std::cout << "Bitte geben sie eine Zahl ein!" << std::endl;
            std::cin.clear();               //Fehlerstatus von cin wird zurückgesetzt
            std::cin.ignore(1000, '\n');    //Ersten 1000 Zeichen werden ignoriert; Alle Zeichen bis zu einem Enter werden überlesen
        }
        switch (auswahl) {
        case 1:

            //Funktion noch zu integrieren

            std::cout << "Rematch" << std::endl;
            eingabeKorrekt = 0;
            break;
        case 2:

            //Funktion noch zu integrieren

            std::cout << "Hauptmenue" << std::endl;
            eingabeKorrekt = 0;
            break;
        case 3:
            eingabeKorrekt = 0;
            break;
        default:
            std::cout << "Ungueltige Eingabe!" << std::endl;
            break;
    }
    } while (eingabeKorrekt != 0);
    return 0;
}


int main() {
    GameRessources gameRessource;
    gameRessource.printBoxMessage("Dies ist definitiv ein sehr sehr offizieller Fehler", "Hinweis");
    int test = gameRessource.printMenue();
    std::cout << test << std::endl;

    //start();
    
    /*
    PlayerBoard testPlayerBoard;
    testPlayerBoard.printBoard();
    testPlayerBoard.placeShips();
    testPlayerBoard.printBoard();
    */

    /*k
    ComputerBoard testComputerBoard;
    testComputerBoard.printBoard();
    testComputerBoard.placeShips();
    testComputerBoard.printBoard();
    */

    return 0;
}

