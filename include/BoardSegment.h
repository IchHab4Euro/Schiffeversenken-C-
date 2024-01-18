#ifndef BOARDSEGMENT_H
#define BOARDSEGMENT_H

#include "Ship.h"
#include <iostream>

enum class SegmentState {Ship, ShipHit, ShipPlacement, Water};

class BoardSegment {
    public:
        BoardSegment(SegmentState initState);
        SegmentState fieldState;
        Ship* shipOnSegment;
        bool isShip();
        bool isShipHit();
        bool isShipPlacement();
        bool isWater();
        void setShipOnSegment(Ship* ship);
        Ship* getShipOnSegment();   
};

#endif