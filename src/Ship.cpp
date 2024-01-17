#include "../include/Ship.h"

int Ship::nextId = 1; 

Ship::Ship(std::string name, int length) : name(name), length(length) {
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

bool Ship::isShipSunk() const{
    for(BoardSegment* shipSegment : BoardSegments){
        if(!(shipSegment->isShipHit())){
            return false; 
        }
    }
    return true; 
}