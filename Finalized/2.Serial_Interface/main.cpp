/*                   INTERFACE SERIAL - ARDUINO - PC

  Iterface with arduino and PC via serial port.

   Example:

  #include "Sinterface.h"

  Sinterface InterfacePC;

  void setup(){
   Serial.begin(9600);
  }

  void serialEvent(){
  //Code to run when there is data available on buffer
    InterfacePC.getCmd();
  }

  void loop(){

    //Comando simples
    if(InterfacePC.analyze("Comando","Resposta terminal")){
      //Code here 
    }

    //Comando do tipo tempo=1000 (Utilizo o valor depois do igual)
    if(InterfacePC.analyze("tempo","Novo tempo configurado")){
      time = atol(InterfacePC.receivedValue);   
    }

    //Configuro uma resposta caso não encontre um comando válido
    InterfacePC.verifyNoCommands("Comando não reconhecido!",0)

  }

  Author: Lucas Cordeiro de Arruda. 
  License: Personal.

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