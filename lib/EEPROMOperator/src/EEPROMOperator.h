#ifndef EEPROMOPERATOR_H
#define EEPROMOPERATOR_H

#include <EEPROM.h>
#include <Arduino.h>

class EEPROMOperator{
public:
  void saveCells(byte *cells);
  byte* getCells();
};

static int CELLS_START=0;

#endif //EEPROMOPERATOR_H
