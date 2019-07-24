/*
  .h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"

#ifndef Sinterface_h
#define Sinterface_h

class Sinterface
{
  public:
    void verifyNoCommands(const char text[], bool debug);
    void getCmd();
    bool analyze(const char cmd[], const char response[]);
    char receivedValue[50];
  private:
    int _pin;
    bool receivedCmdFlag = false;
    int receivedPointer = 0;
    char receivedCmd[50];
};

#endif