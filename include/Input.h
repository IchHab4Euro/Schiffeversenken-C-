#ifndef INPUT_H
#define INPUT_H

#include <iostream>

/*
    static class Input
    handles the Input of the User
*/
class Input  {
    public: 
        // input cordinates, error if wrong input,
        static std::string userinputCoordinates(std::string pMessage, int pBoardSize);

        // input Int, error if wrong Input, int must be bound of lower an upper
        static int userinputInt(std::string pMessage, int pLower, int pUpper);
};
#endif