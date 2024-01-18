#ifndef INPUT_H
#define INPUT_H

#include <iostream>

class Input  {
    public: 
        static std::string userinputCoordinates(std::string pMessage, int pBoardSize);
        static int userinputInt(std::string pMessage, int pLower, int pUpper);
};
#endif