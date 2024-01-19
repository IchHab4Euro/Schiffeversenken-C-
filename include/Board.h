#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"
#include "BoardSegment.h"
#include <iostream>
#include <vector>

enum class Direction {North, East, South, West};

/*
    Abstract Class Board:
    represents a Board of a Player or a Computer
*/
class Board {

public:
    
    Board();
    void init(std::vector<BoardSegment*> initBoardSegments, std::vector<Ship*> initShips, bool gamePhase);
    
    //to initialize the Board with a grid and and the ships
    void init(std::vector<BoardSegment*> initBoardSegments, std::vector<Ship*> initShips);
    
    //Abstract Method to Place All Ships on the Board
    virtual void placeShips() = 0;
    
    //Abstract Mehtod to attack the board of the enemy
    virtual void attack(Board* enemyBoard) = 0; 
    
    //returning bordSize
    int getBoardSize();
    
    //returning alls Ships not placed on the Board
    std::vector<Ship*> getShipsNextToBoard();
    
    //returning all Ships placed on the Board
    std::vector<Ship*> getShipsOnBoard();

    //sets a Ship sunk if alls its BoardSegments are Hit
    void setSunkenShips();

    //returns true if all Ships on the Board are sunken
    bool allShipsSunk() const;

    //hold the size of the Board
    int const boardSize = 10;
    
    //holds the Segments of the Board in a grid
    BoardSegment* grid[10][10]; 

protected:
    //Places the Ship on a given latitude an longitude
    bool placeShip(int latitude, int longitude, Direction direction, Ship* ship);

    //checks if the Placement of a Ship is valid, is the ship inside of the grid
    bool isValidPlacement(int latitude, int longitude, Direction direction, Ship* ship) const;

    //returns the Segment in the given direction from the lat lon value
    BoardSegment* getSegmentToPlace(int latitude, int longitude, Direction direction, int offset) const;

    //returns the Direction to a given Number
    Direction numberToDirection(int number) const;
    
    //returns the Latitude throw a given cordinate as String Like: A1
    int cordinateToLatitude(const std::string cordinate) const;
    
    //returns the Longitude throw a given cordinate as String Like: A1
    int cordinateToLongitude(const std::string cordinate) const;
    
    //checks for Collisions with outher Ships
    bool checkForColission();
    
    //replaces the placement of the ship with the given state
    void replaceShipPlacement(SegmentState newState, Ship* shipToPlace);
    
    //holds the inital Ships to be able to Reset the whole Board;
    std::vector<Ship*> initShipsReset;
    
    //holds the ships not placed on the Board
    std::vector<Ship*> shipsNextToBoard;
    
    //holds the ships places on the Board
    std::vector<Ship*> shipsOnBoard;
     
private:
    
    
    
    //Sammlung aller Spielfelder ungeordnet
};
#endif