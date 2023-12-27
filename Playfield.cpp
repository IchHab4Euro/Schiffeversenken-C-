#include "Headerdateien\PlayField.h"

#include <iostream>
#include <fstream>

PlayField::PlayField(){
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            grid[i][j] = '~';
        }
    }
}

void PlayField::printField() const {
    for (int i = -1; i < 11; i++)
    {
        if (i == -1 || i == 0)
        {
            std::cout << " ";
        } else {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;

    char c = 'A';
    for (int i = 0; i < 10; i++)
    {
        std::cout << c << "|";
        for (int j = 0; j < 10; j++)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << "|" << std::endl;
        c++;
    }
}


void PlayField::saveToFile(const std::string& filename) const {
    std::ofstream saveFile (filename);

    if(!saveFile.is_open()){
        std::cerr << "Unable to open File!" << std::endl;
        return;
    }

    std::string saveString = gameID + splitSymbol + playerID;

    for(int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j){
            saveString = saveString + splitSymbol + grid[i][j];
        }
    }
    saveFile << saveString << std::endl;
}