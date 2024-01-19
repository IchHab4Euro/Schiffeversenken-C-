#include "../include/Ship.h"

int Ship::nextId = 1; 

Ship::Ship(std::string name, int length, bool isSunken) : name(name), length(length), sunk(sunk) {
    id = nextId;
    nextId++;
}

std::string Ship::getName() const {
    return name;
}

int Ship::getLength() const {
    return length;
}

int Ship::getId() const {
    return id;
}

bool Ship::isSunken(){
    return sunk;
}
