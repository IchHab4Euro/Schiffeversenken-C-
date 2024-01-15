#ifndef BOARDFIELD_H
#define BOARDFIELD_H

enum class BoardFieldState {
    Water,
    ShipPlacement,
    Ship
};

class BoardField  {
    public: 
        BoardField();
        BoardFieldState getState() const;
        void setState(BoardFieldState boardFieldState);
    private:
        BoardFieldState state;
};
#endif