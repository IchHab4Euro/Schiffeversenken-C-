#ifndef SHIP_H 
#define SHIP_H

#include <string>
#include <vector>

/*
    class Ship
    represents a Ship
*/
class Ship {
public:
    Ship(std::string name, int length, bool sunk, int ID);
    std::string getName() const;
    int getLength() const;
    int getId() const;
    bool isSunken();
    void setSunken();

    std::string name;
    int length;
    int id; 
    bool sunk = false;
private:
    
};
#endif