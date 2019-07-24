/*
  Sinterface.cpp - Library for PC and arduino terminal communication.
  Created by Lucas C. Arruda, July 22, 2019.
  All rights reserveds. 

*/

#include "Arduino.h"
#include "Sinterface.h"

//Use it on function void serialEvent() to detect commands
void Sinterface::getCmd(){
 
  //Code to run when there is data available on buffer

  char receivedCharacter; 

  //If the last command was processed, the new comand is taken from buffer.
  if (!receivedCmdFlag){

    //gets the character from serial buffer
    receivedCharacter = Serial.read();
    //returns the character 
    Serial.write(receivedCharacter);     

    //store the character in buffer
    receivedCmd[receivedPointer] = receivedCharacter;
    receivedPointer++;
    
    //If backspace is pressed, sobrescribe previous strings 
    if((receivedCharacter == 8) & (receivedPointer >= 2)){
      receivedPointer-=2;
    } 

    //If command is given, the null chacter is placed 
    //and a flag is set. 
    if (receivedCharacter == '\n'){
        
        //Form the string with only the command
        int i;
        bool cmdFlag = false;
        for(i = 0; i < 50; i++){
          if (receivedCmd[i] == '='){
            receivedCmd[i] = 0;
            cmdFlag = true;
            break;
          } 
        }

        //Inserts the null character
        //command type: comand only, no value and =
        if (cmdFlag == false){
          receivedCmd[receivedPointer-2]=0;
        }
        
        //Gets the value 
        int j;
        int k = 0;
        if (cmdFlag == true){
          for(j = i + 1; (j < 50) & (receivedCmd[j] != '\n'); j++){
            receivedValue[k] = receivedCmd[j];
            k++;
          }
          receivedValue[k-1] = 0;
        }

      receivedCmdFlag = 1;
      receivedPointer = 0;   
    }
  }
}

//Use it on void loop() to detect and execute commands 
bool Sinterface::analyze(const char cmd[], const char response[]){

    bool resp = false;

    if (!strcmp(receivedCmd, cmd) & (receivedCmdFlag == true)) {
      Serial.print("-- ");
      Serial.println(response);
      receivedCmdFlag = false;
      resp = true;
    }

    return resp;

}

//Use it on void loop () after all the commands, to detect incorrect commands
void Sinterface::verifyNoCommands(const char text[], bool debug){

  if (receivedCmdFlag == true){
    Serial.print("-- ");
    Serial.println(text);
    receivedCmdFlag = false;

    if (debug){ 
      Serial.println(receivedValue);
      Serial.println(receivedCmd);

      for(int i=0; i<50; i++){
        Serial.print(receivedValue[i],HEX);
      }
      Serial.println("");
      for(int i=0; i<50; i++){
        Serial.print(receivedCmd[i],HEX);
      }
      Serial.println("");
    }

    receivedCmd[0] = 0;
    receivedValue[0] = 0; 
  }
}