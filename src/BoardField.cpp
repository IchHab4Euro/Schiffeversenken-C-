#include "../include/BoardField.h"

BoardField::BoardField() {   
    state = BoardFieldState::Water;
}

BoardFieldState BoardField::getState() const {
    return state;
}

void BoardField::setState(BoardFieldState boardfieldstate){
    state = boardfieldstate;
}
