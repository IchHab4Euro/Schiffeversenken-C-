#ifndef OUTPUT_H
#define OUTPUT_H

#include "Board.h"
#include "PlayerBoard.h"
#include <iostream>
#include <vector>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

class Output  {
    public:
        Output(); 
        void printMenue(std::vector<std::string> pMenuePoints);
        void printBoxError(std::string errorMessage);
        void printBoxMessage(std::string textMessage);
        void printPlayerBoard(Board* board);
        void printBothBoards(Board* pBoardPlayer, Board* pBoardComputer);
        void printBoardWithMenue(Board* pBoard, std::vector<Ship*> pMenue);
        void printWelcome();
        void printWin();
        void printLose();

    private:
        const int boxWidth = 30;
        void printRow(Board* board, int pRow);
        void printRowTwoBoards(Board* pPlayer, Board* pComputer, int pRow);
        int printRowMenue(Board* board, std::vector<Ship*> pMenue, int pRow, int pMenuePos);
        std::string printShipNameAndLength(std::vector<Ship*> pMenue, int pMenuePos);
   
};
#endif