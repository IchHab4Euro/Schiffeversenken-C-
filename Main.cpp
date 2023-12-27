#include "Headerdateien/Playfield.h"

#include <iostream>

int start()  {
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
    start();
    //PlayField testField;
    //testField.printField();
    //testField.saveToFile("FieldSave.csv");
    return 0;
}

