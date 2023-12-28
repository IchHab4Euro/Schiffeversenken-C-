#pragma once

#include "Board.h"

#include <iostream>

class PlayerBoard : public Board {
    public:
        void placeShips() override;
};