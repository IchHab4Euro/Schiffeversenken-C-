#include "Headerdateien/Playfield.h"

#include <iostream>

int main() {
    PlayField testField;
    testField.printField();
    testField.saveToFile("FieldSave.csv");
}
