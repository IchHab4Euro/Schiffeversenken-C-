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
    
    virtual void placeship() = 0;
    void printField() const;

private:
    char grid[10][10]; 
};

void Field::printField() const {
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
