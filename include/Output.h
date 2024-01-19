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

/*
    static class Output
    handles the Output on the CommandLine
*/
class Output  {
    public:
        Output(); 
        static void printMenue(std::vector<std::string> pMenuePoints); //prints a Menue with given Points
        static void printBoxError(std::string errorMessage, bool textAdjust); //prints an error inside a box
        static void printBoxMessage(std::string textMessage, bool textAdjust); //prints Message inside a box
        static void printPlayerBoard(Board* board);//prints one Board
        static void printBothBoards(Board* pBoardPlayer, Board* pBoardComputer); //prints the Board of the Player an the Enemy (Computer -> Ships are not visible)
        static void printBoardWithMenue(Board* pBoard, std::vector<Ship*> pMenue);//in ship Placment Phase Board + Ships to place
        static void printWelcome(); //Welcome Message
        static void printWin(); //Win Message
        static void printLose(); //Lose Message

    private:
        static const int boxWidth = 40;

        //helper Methods for printing the Board:
        static void printRow(Board* board, int pRow);
        static void printRowTwoBoards(Board* pPlayer, Board* pComputer, int pRow);
        static int printRowMenue(Board* board, std::vector<Ship*> pMenue, int pRow, int pMenuePos);
        static std::string printShipNameAndLength(std::vector<Ship*> pMenue, int pMenuePos);
   
};
#endif