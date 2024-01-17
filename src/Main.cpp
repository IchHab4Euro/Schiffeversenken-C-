#include "../include/PlayerBoard.h"
#include "../include/ComputerBoard.h"
#include "../include/Ship.h"
#include "../include/Output.h"

#include <iostream>
/*
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
    Output output;
    ComputerBoard computerBoard;
    PlayerBoard playerboard;
    std::vector<Ship> menue;
    Ship Schlachtschiff("Schlachtschiff",5);
    Ship Kreuzer1("Kreuzer1",4);
    Ship Kreuzer2("Kreuzer2",4);
    Ship Boot("Boot", 2);
    menue.push_back(Schlachtschiff);
    menue.push_back(Kreuzer1);
    menue.push_back(Kreuzer2);
    menue.push_back(Boot);
    std::vector<Ship>* menuezeiger = &menue;
    Board* playerzeiger = &playerboard;
    Board* computerZeiger = &computerBoard;
    output.printBoardWithMenue(playerzeiger, menuezeiger);
}*/