#include "Headerdateien/ShipSegment.h"

ShipSegment::ShipSegment() : state(ShipSegmentState::NotHit) {}

ShipSegmentState ShipSegment::getState() const {
    return state;
}

void ShipSegment::hit() {
    state = ShipSegmentState::Hit;
}