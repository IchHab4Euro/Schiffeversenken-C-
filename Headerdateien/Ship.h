#ifndef SHIP_H //sollen wir das so überal machen?
#define SHIP_H

#include <string>

class Ship {
public:
    Ship(std::string name, int length);
    std::string getName() const;
    int getLength() const;

private:
    std::string name;
    int length;
};

#endif