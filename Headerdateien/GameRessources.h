#ifndef GAMERESSOURCES_H
#define GAMERESSOURCES_H

#include <iostream>

class GameRessources {
public:
    void printWelcome();
    void printWin();
    void printLose();
    void printBoxMessage(std::string, std::string);
    int printMenue();
    int userinputInt(std::string message, int lower, int upper);
    std::string userinputString(std::string pMessage);
    std::string userinputCoordinates(std::string pMessage, int pBoardSize);

private:
    int boxWidth = 30;

};
#endif