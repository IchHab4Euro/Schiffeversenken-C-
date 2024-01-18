#ifndef SHIP_H 
#define SHIP_H

#include <string>
#include <vector>

class Ship {
public:
    Ship(std::string name, int length, bool sunk);
    std::string getName() const;
    int getLength() const;
    int getId() const;
    bool isSunken();

    std::string name;
    int length;
    int id; 
    bool sunk;
    
    static int nextId; 

private:
    
};
#endif