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

private:
    int boxWidth = 30;

};
#endif