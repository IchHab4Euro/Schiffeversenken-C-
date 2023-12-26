#include <iostream>

class Field {
public:
    Field() {
        for (int i = 0; i < 10 ; ++i){
            for (int j = 0; j < 10; ++j){
                grid[i][j] = '~';
            }
        }
    }
    
    void printField() const;

    virtual void placeShip() = 0;

private:
    char grid[10][10]; 
};