#ifndef SHIPSEGMENT_H
#define SHIPSEGMENT_H

enum class ShipSegmentState {
    NotHit,
    Hit
};

class ShipSegment  {
    public: 
        ShipSegment();

        ShipSegmentState getState() const;

        void hit();
    
    private:
        ShipSegmentState state;
};
#endif