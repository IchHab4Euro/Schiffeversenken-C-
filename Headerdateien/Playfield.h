#pragma once

#include <iostream>

class PlayField {
public:
    PlayField();
    void printField() const;
    void saveToFile(const std::string& filename) const;
    int longitudeToIndex(const std::string cordinate) const;
    int latitudeToIndex(const std::string cordinate) const;

    virtual void placeShips();

private:
    char grid[10][10]; //Magic Number entfernen
    int indexGrid[10][10]; //Magic Numbers entfernens
    std::string gameID = "1";
    std::string playerID = "1";
    char splitSymbol = ';';
};
