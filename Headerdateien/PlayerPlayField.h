#pragma once

#include "PlayField.h"

#include <iostream>

class PlayerPlayField : public PlayField {
    public:
        void placeShips() override;
};