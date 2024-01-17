#ifndef BOARDSEGMENT_H
#define BOARDSEGMENT_H


struct BoardSegment {
    enum class FieldState {Ship, ShipHit, ShipPlacement, Water};
    BoardSegment(FieldState initState);
    FieldState fieldState;
    bool isShip();
    bool isShipHit();
    bool isShipPlacement();
    bool isWater();
};

#endif