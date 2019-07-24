/*                   INTERFACE SERIAL - ARDUINO - PC

    Aplication example. 

 */

#include <Arduino.h>
#include "Sinterface.h"

Sinterface InterfacePC;
int time = 500;


void serialEvent(){
//Code to run when there is data available on buffer
  InterfacePC.getCmd();
}

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {

    if(InterfacePC.analyze("tempo","Novo tempo configurado")){
      time = atol(InterfacePC.receivedValue);
      Serial.println(time);
      InterfacePC.receivedValue[0] = 0;
    }

    if (InterfacePC.analyze("pisca","Pisca led!")){ 
      digitalWrite(13,HIGH);
      delay(time);
      digitalWrite(13,LOW);
      delay(time);
      digitalWrite(13,HIGH);
      delay(time);
      digitalWrite(13,LOW);
    } 

    if (InterfacePC.analyze("apaga","Led apagado!")){
      digitalWrite(13,LOW);
    }

    if (InterfacePC.analyze("acende","Led aceso!")){
      digitalWrite(13,HIGH);
    }

    InterfacePC.verifyNoCommands("Comando não reconhecido!",0);

  }