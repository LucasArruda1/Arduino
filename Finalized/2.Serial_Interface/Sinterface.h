/*
  Sinterface.h
  
  Creates an iterface with arduino and PC via serial port via command line. 

  Example on command line:

  ledOn
  -- Led On! 


  Use in code:

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