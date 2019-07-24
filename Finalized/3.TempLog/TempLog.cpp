/*
   TEMPERATURE DATA LOG -----------------------------------------
  
   LUCAS CORDEIRO DE ARRUDA

   Saves temperature data in EEPROM and print the result in 
   serial port

   Output:  LED_RD - If equals 1 indicates that datalog is running
            LED_GN - If equals 1 indicates that datalog is not run. 

   Serial port commands:  
   
   1 "Start" - Initiate the log, the initial time is required.  
   2 "Stop"  - Reset the log. 
   3 "Print" - Prints on the serial port all the data recorded. 

  ----------------------------------------------------------------
*/

#include "Arduino.h"
#include <EEPROM.h>

#define LedGreenPin 4
#define LedRedPin 5

#define analogInput A0

#define turnGreenOnCMD "GON"
#define turnGreenOffCMD "GOFF"

int sensorValue; 

boolean cmdInitiate = 0;
boolean cmdStop = 0; 
boolean cmdShowdata = 0;

int temperature; 

//EEPROM
int addr = 0;

//Total time: 10h = 600 min
//Sample time: 2 min -> 300 samples
byte logData[500];
int sample = 0; 
int maxSamples = 300;
unsigned long sampleTime_ms =  120000; 

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;     // whether the string is complete

void setup()
{
  analogReference(INTERNAL);      //Set reference voltage to 1.1V = 1023
  pinMode(LedGreenPin, OUTPUT);   //Initiate ports
  pinMode(LedRedPin, OUTPUT);


  // initialize serial:             //SERIAL PORT
  Serial.begin(9600);

  digitalWrite(LedGreenPin, LOW);  //LEDS
  digitalWrite(LedRedPin, LOW);

}

void serialEvent() {

 while (Serial.available() > 0) {
   char incomingCharacter = Serial.read();
   switch (incomingCharacter) {
      case '1':                           //INICIA A COLETA DE DADOS
       digitalWrite(LedRedPin, HIGH);  
       digitalWrite(LedGreenPin, LOW);
       cmdInitiate = 1;
       cmdStop = 0;
       cmdShowdata = 0; 
      break;
 
      case '2':                           //ENCERRA A COLETA DE DADOS
        digitalWrite(LedRedPin, LOW);  
        digitalWrite(LedGreenPin, HIGH);  
        cmdInitiate = 0;
        cmdStop = 1;
        cmdShowdata = 0; 
      break;

      case '3':                           //IMPRIME TODOS OS DADOS
        digitalWrite(LedRedPin, LOW);  
        digitalWrite(LedGreenPin, LOW);  
        cmdInitiate = 0;
        cmdStop = 0;
        cmdShowdata = 1; 
      break;

    }
 }
}

/*
   0 to 1.1 volts, to a digital value between 0 and 1023.
   LM35 outputs 10mV/°C - 0°C = 0mV

*/
void loop() {

  if (sample >= maxSamples){    //Stop data aquisiton 

    cmdInitiate = 0; 
    cmdStop = 1; 
    digitalWrite(LedGreenPin, HIGH);  
    digitalWrite(LedRedPin, LOW);

  }

  if (cmdInitiate == 1){

    sensorValue = analogRead(analogInput);  
    
    //temperature = 110*sensorValue/1023;

    sample += 1;                  
    //logData[sample] = sensorValue;

    addr = sample;
    EEPROM.write(addr, sensorValue);

    //Serial.print("temperature:");
    //Serial.print(EEPROM.read(addr)); 
    //Serial.print('\n'); 

    _delay_ms(sampleTime_ms);

  }
 
 if (cmdShowdata == 1){

   Serial.print("LOGGED TEMPERATURE DATA\n");
   Serial.print("Sample time: 2 minutes, Start time: 22:30h 08/07/2019\n");
   Serial.print("Signal: 10mV/°C 0-1.1V 1023 values. Sensor: LM35\n");

   for (int i = 0; i<300; i++){       //Mostra todos os dados gravados 
     Serial.print(EEPROM.read(i));       //em formato csv
     Serial.print(';');
     Serial.print(i);
     Serial.print('\n');
   }
  
  cmdShowdata = 0;
  }
  
}