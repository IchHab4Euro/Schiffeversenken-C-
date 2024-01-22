#include "../include/Ship.h"

Ship::Ship(std::string name, int length, bool isSunken, int id) : name(name), length(length), sunk(sunk), id(id)  {

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

void Ship::setSunken() {
    sunk = true;
}