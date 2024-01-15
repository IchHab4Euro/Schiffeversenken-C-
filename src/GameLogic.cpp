#include "../include/GameLogic.h"
#include "../include/PlayerBoard.h"
#include "../include/ComputerBoard.h"


GameLogic::startGame(){

    int boardSize = 10; 

    PlayerBoard playerBoard(boardSize);
    ComputerBoard computerBoard(boardSize);

    Board* board1 = &playerBoard;
    Board* board2 = &playerBoard;

    board1->placeShips();
    board2->placeShips();


}