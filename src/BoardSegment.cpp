#include "../include/BoardSegment.h"

BoardSegment::BoardSegment(SegmentState initState) : fieldState(initState), shipOnSegment(nullptr) {}

bool BoardSegment::isShip() {
    return fieldState == SegmentState::Ship;
}

bool BoardSegment::isShipHit() {
    return fieldState == SegmentState::ShipHit;
}

bool BoardSegment::isShipPlacement() {
    return fieldState == SegmentState::ShipPlacement;
}

bool BoardSegment::isWater() {
    return fieldState == SegmentState::Water;
}

void BoardSegment::setShipOnSegment(Ship* ship) {
    this->shipOnSegment = ship;
}

Ship* BoardSegment::getShipOnSegment() {
    return shipOnSegment;
}