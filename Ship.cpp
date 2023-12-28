#include "Headerdateien/ship.h"

Ship::Ship(std::string name, int length) : name(name), length(length) {}

std::string Ship::getName() const {
    return name;
}

int Ship::getLength() const {
    return length;
}