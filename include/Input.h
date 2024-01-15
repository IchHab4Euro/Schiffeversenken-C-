#ifndef INPUT_H
#define INPUT_H

#include <iostream>

class Input  {
    public: 
        std::string userinputCoordinates(std::string pMessage, int pBoardSize);
        int userinputInt(std::string pMessage, int pLower, int pUpper);
   
};
#endif