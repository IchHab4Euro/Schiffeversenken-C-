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

    /*
    Ship Zerstoerer1("Zerstoerer1",3);
    Ship Zerstoerer2("Zerstoerer2",3);
    Ship Zerstoerer3("Zerstoerer3",3);
    Ship UBoot1("U-Boot1",2);
    Ship UBoot2("U-Boot2",2);
    Ship UBoot3("U-Boot3",2);
    Ship UBoot4("U-Boot4",2);
    */

    shipsNextToBoard.push_back(Schlachtschiff);
    shipsNextToBoard.push_back(Kreuzer1);
    shipsNextToBoard.push_back(Kreuzer2);
    
    /*
    shipsNextToBoard.push_back(Zerstoerer1);
    shipsNextToBoard.push_back(Zerstoerer2);
    shipsNextToBoard.push_back(Zerstoerer3);   
    shipsNextToBoard.push_back(UBoot1);
    shipsNextToBoard.push_back(UBoot2);
    shipsNextToBoard.push_back(UBoot3);
    shipsNextToBoard.push_back(UBoot4);
    */
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

int Board::cordinateToLatitude(const std::string cordinate) const {
    if (cordinate.length() == 2){
        int latitude = cordinate[0] - 'A';
        return latitude;
    }
    return 0;
}

int Board::cordinateToLongitude(const std::string cordinate) const {
    if (cordinate.length() == 2){
        int longitude = cordinate[1] - '1';
        return longitude;
    }
    return 0;
}

bool Board::placeShip(int latitude, int longitude, Direction direction, Ship ship) {
    switch (direction)
    {
    case Direction::Down: //unten
        if(latitude + ship.getLength() >= boardSize){
            return false;
        }
        for(int i = 0; i < ship.getLength(); i++){
            if(grid[latitude + i][longitude] == waterSymbol){
                grid[latitude + i][longitude] = shipPlaceSymbol;
            }
        }
        break;
    case Direction::Up://oben
        if(longitude - ship.getLength() <= 0){
            return false;
        }
        for(int i = 0; i < ship.getLength(); i++){
            if(grid[latitude - i][longitude] == waterSymbol){
                grid[latitude - i][longitude] = shipPlaceSymbol;
            }
        }
        break;
    case Direction::Right://rechts
        if(longitude + ship.getLength() >= boardSize){
            return false;
        }
        for(int i = 0; i < ship.getLength(); i++){
            if(grid[latitude][longitude + i] == waterSymbol){
                grid[latitude][longitude + i] = shipPlaceSymbol;
            }
        }
        break;
    case Direction::Left://links
        if(longitude - ship.getLength() <= 0){
            return false;
        }
        for(int i = 0; i < ship.getLength(); i++){
            if(grid[latitude][longitude - i] == waterSymbol){
                grid[latitude][longitude - i] = shipPlaceSymbol;
            }
        }
        break;
    default:
        std::cerr<<"Falsche eingabe"<<std::endl;
        return false;
        break;
    }

    if(checkForColission()){
        std::cerr<<"Es kommt zu einer Kollision!"<<std::endl;
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

Direction Board::numberToDirection(int number)  const { 
    switch (number) {
        case 0:
            return Direction::Down;
        case 1:
            return Direction::Up;
        case 2:
            return Direction::Right;
        case 3:
            return Direction::Left;
        default:
            throw std::invalid_argument("Invalid number for Direction"); //werden einer Exc. sollten wir öfters machen und gekonnt abfangen!
    }
}

/*
bool Board::isValidPlacement(int latitude, int longitude, Ship ship) const{
    if(latitude + ship.getLength() < boardSize && (longitude + ship.getLength() < boardSize || longitude - ship.getLength() > 0) ||
        (latitude + ship.getLength() < boardSize || latitude - ship.getLength() > 0) && (longitude + ship.getLength() < boardSize)){
        return true;
    }
    else{
        return false; 
    }
}
*/