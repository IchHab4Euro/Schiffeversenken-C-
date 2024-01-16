#ifndef OUTPUT_H
#define OUTPUT_H

#include "Board.h"
#include <iostream>
#include <vector>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

class Output  {
    public: 
        int printMenue(std::vector<std::string> pMenuePoints);
        void printBoxMessage(std::string textMessage, std::string type);
        void printBoard(Board* board);
        void printRow(Board* board, int pRow);
        void printWelcome();
        void printWin();
        void printLose();

    private:
        int boxWidth = 30;
   
};
#endif