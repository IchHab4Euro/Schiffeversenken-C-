#include "../include/Ship.h"

ShipSegment::ShipSegment() : state(State::NoHit) {}

void ShipSegment::hit() {
    state = State::Hit;
}

bool ShipSegment::isHit() const {
    return state == State::Hit;
}

int Ship::nextId = 1; 

Ship::Ship(std::string name, int length) : name(name), length(length) {
    id = nextId;
    nextId++;

    for(int i = 0; i < length; i++){
        shipComponents.push_back(ShipSegment());
    }
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
    for(const ShipSegment& shipSegment : shipComponents){
        if(!shipSegment.isHit()){
            return false; 
        }
    }
    return true; 
}