#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
class InvalidShipPlacement : public std::exception {
    std::string info() {
        return "Das Schiff darf so nicht platziert werden";
    }
};


#endif