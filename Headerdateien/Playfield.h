#pragma once

#include <iostream>

class PlayField {
public:
    PlayField();
    void printField() const;
    void saveToFile(const std::string& filename) const;

private:
    char grid[10][10];
    std::string gameID = "1";
    std::string playerID = "1";
    char splitSymbol = ';';
};