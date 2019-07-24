#include "Arduino.h"
#include "Morse.h"

int pin = 13;
Morse morse(pin);

void setup(){

}

void loop()
{
  morse.dot(); morse.dot(); morse.dot();
  morse.dash(); morse.dash(); morse.dash();
  morse.dot(); morse.dot(); morse.dot();
  delay(3000);
} 


