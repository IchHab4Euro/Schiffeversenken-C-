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
        Output(); 
        void printMenue(std::vector<std::string> pMenuePoints);
        void printBoxMessage(std::string textMessage, std::string type);
        void printPlayerBoard(Board* board);
        void printRow(Board* board, int pRow);
        void printBothBoards(Board* pBoardPlayer, Board* pBoardComputer);
        void printRowTwoBoards(Board* pPlayer, Board* pComputer, int pRow);
        void printBoardWithMenue(Board* pBoard, std::vector<Ship>* pMenue);
        int printRowMenue(Board* board, std::vector<Ship>* pMenue, int pRow, int pMenuePos);
        std::string printShipNameAndLength(std::vector<Ship>* pMenue, int pMenuePos);
        void printWelcome();
        void printWin();
        void printLose();

    private:
        int boxWidth = 30;
   
};
#endif