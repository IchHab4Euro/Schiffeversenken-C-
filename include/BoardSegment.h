#ifndef BOARDSEGMENT_H
#define BOARDSEGMENT_H

#include "Ship.h"
#include <iostream>

enum class SegmentState {Ship, ShipHit, Water, WaterHit, Revealed, ShipPlacement};

class BoardSegment {
    public:
        BoardSegment(SegmentState initState);
        ~BoardSegment();
        SegmentState fieldState;
        Ship* shipOnSegment;
        
        bool isShip();
        bool isShipHit();
        bool isWater();
        bool isWaterHit();
        bool isRevealed();
        bool isShipPlacement();
        

        void setShip();
        void setShipHit();
        void setWater();
        void setWaterHit();
        void setRevealed();
        void setShipPlacement();
        
        void setShipOnSegment(Ship* ship);
        Ship* getShipOnSegment();   
};

#endif