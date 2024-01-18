#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <vector>
#include "Board.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define GREY "\033[1;30m"
#define RESET "\033[0m"
#define BLUE "\033[1;34m"

class Output  {
    public:
        Output(); 
        static void printMenue(std::vector<std::string> pMenuePoints);
        static void printBoxError(std::string errorMessage, bool textAdjust);
        static void printBoxMessage(std::string textMessage, bool textAdjust);
        static void printPlayerBoard(Board* board);
        static void printBothBoards(Board* pBoardPlayer, Board* pBoardComputer);
        static void printBoardWithMenue(Board* pBoard, std::vector<Ship*> pMenue);
        static void printWelcome();
        static void printWin();
        static void printLose();

    private:
        static const int boxWidth = 40;
        static void printRow(Board* board, int pRow);
        static void printRowTwoBoards(Board* pPlayer, Board* pComputer, int pRow);
        static int printRowMenue(Board* board, std::vector<Ship*> pMenue, int pRow, int pMenuePos);
        static std::string printShipNameAndLength(std::vector<Ship*> pMenue, int pMenuePos);
   
};
#endif