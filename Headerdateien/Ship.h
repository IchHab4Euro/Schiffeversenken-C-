#ifndef SHIP_H //sollen wir das so überal machen?
#define SHIP_H

#include <string>

class Ship {
public:
    Ship(std::string name, int length);
    std::string getName() const;
    int getLength() const;
    int getId() const;

private:
    std::string name;
    int length;
    int id;

    static int nextId; 
};

#endif