#include "Headerdateien/Board.h"
#include "Headerdateien/Ship.h"

#include <iostream>
#include <fstream>

Board::Board(){
    for (int i = 0; i < boardSize; ++i) { //Magic Numbers
        for (int j = 0; j < boardSize; ++j) {
            grid[i][j] = waterSymbol;
        }
    }

    Ship Schlachtschiff("Schlachtschiff",5);
    Ship Kreuzer1("Kreuzer1",4);
    Ship Kreuzer2("Kreuzer2",4);
    Ship Zerstoerer1("Zerstoerer1",3);
    Ship Zerstoerer2("Zerstoerer2",3);
    Ship Zerstoerer3("Zerstoerer3",3);
    Ship UBoot1("U-Boot1",2);
    Ship UBoot2("U-Boot2",2);
    Ship UBoot3("U-Boot3",2);
    Ship UBoot4("U-Boot4",2);

    shipsNextToBoard.push_back(Schlachtschiff);
    shipsNextToBoard.push_back(Kreuzer1);
    shipsNextToBoard.push_back(Kreuzer2);
    shipsNextToBoard.push_back(Zerstoerer1);
    shipsNextToBoard.push_back(Zerstoerer2);
    shipsNextToBoard.push_back(Zerstoerer3);   
    shipsNextToBoard.push_back(UBoot1);
    shipsNextToBoard.push_back(UBoot2);
    shipsNextToBoard.push_back(UBoot3);
    shipsNextToBoard.push_back(UBoot4);
}

void Board::printBoard() const {
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

void Board::saveToFile(const std::string& filename) const {

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

int Board::cordinateToLatitude(const std::string cordinate) const{
    if (cordinate.length() == 2){
        int latitude = cordinate[1] - '1';
        return latitude;
    }
    return 0;
}

int Board::cordinateToLongitude(const std::string cordinate) const{
    if (cordinate.length() == 2){
        int longitude = cordinate[0] - 'A';
        return longitude;
    }
    return 0;
}

bool Board::placeShip(int latitude, int longitude, int direction, Ship ship) {
    if(!direction){
        if(latitude + ship.getLength() > boardSize - 1){
            return false;
        }
        for(int i = 0; i < ship.getLength(); i++){
            if(grid[latitude + i][longitude] == waterSymbol){
                grid[latitude + i][longitude] = shipPlaceSymbol;
            }
        }
    }
     if(direction){
        if(longitude + ship.getLength() > boardSize - 1){
            return false;
        }
        for(int i = 0; i < ship.getLength(); i++){
            if(grid[latitude][longitude + i] == waterSymbol){
                grid[latitude][longitude + i] = shipPlaceSymbol;
            }
        }
    }

    if(checkForColission()){
        replacShipPlaceSymbol(waterSymbol);
        return false;
    }
    else{
        replacShipPlaceSymbol(shipSymbol);
    }
    return true;
}

bool Board::checkForColission() const{
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            if(grid[i][j] == shipPlaceSymbol){
                if(grid[i + 1][j] == shipSymbol || grid[i - 1][j] == shipSymbol || grid[i][j + 1] == shipSymbol || grid[i][j - 1] == shipSymbol){
                    return true; 
                }
            }
        }
    }
    return false; 
}

void Board::replacShipPlaceSymbol(char replacer) {
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            if(grid[i][j] == shipPlaceSymbol){
                grid[i][j] = replacer;
            }
        }
    }
}