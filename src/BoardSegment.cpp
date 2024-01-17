#include "../include/BoardSegment.h"

BoardSegment::BoardSegment(FieldState initState) : fieldState(initState) {}

bool BoardSegment::isShip() {
    return fieldState == FieldState::Ship;
}

bool BoardSegment::isShipHit() {
    return fieldState == FieldState::ShipHit;
}

bool BoardSegment::isShipPlacement() {
    return fieldState == FieldState::ShipPlacement;
}

bool BoardSegment::isWater() {
    return fieldState == FieldState::Water;
}