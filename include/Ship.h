#ifndef SHIP_H 
#define SHIP_H

#include <string>
#include <vector>

class Ship {
public:
    Ship(std::string name, int length, bool isSunken);
    std::string getName() const;
    int getLength() const;
    int getId() const;

    std::string name;
    int length;
    int id; 
    bool isSunken;
    
    static int nextId; 

private:
    
};
#endif