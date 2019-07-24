/*
  Características do projeto: 
  
  - Indicador sonoro de distância.
  - Indicador visual de distância com 4 leds.
  - Ranges configuráveis via projeto. 

  Etapa 1: Teste de todos os componentes
  Etapa 2: Programa simples com o sensor reflexivo
  Etapa 3: Criação do programa. 

 */

#include <Arduino.h>

#define LED1 4
#define LED2 5
#define LED3 6
#define LED4 7

#define BUZZER 8

#define DistanceTrigger 3
#define DistanceEcho 2

volatile unsigned long ReturnTime;
unsigned long InitialTime = 0; 
volatile bool first = false; 
volatile bool sampled = false; 
bool calculated = false;


//BarGraph com 4 Leds
void barGraph(int QtdLeds);

//Get distance sensor time
void getSensorTime();

//Get object distance
float getObjectDistance();

void setup() {

  Serial.begin(9600);

  pinMode(LED1, OUTPUT);  
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(DistanceTrigger, OUTPUT);
  pinMode(DistanceEcho, INPUT);

  attachInterrupt(digitalPinToInterrupt(DistanceEcho), getSensorTime, FALLING);

}

void loop() {
  
  float Distance = getObjectDistance();

  barGraph((int)(Distance*10)-2);

  Serial.println((float)Distance,3);

  delay(500);

}


void barGraph(int QtdLeds){


  switch (QtdLeds)
  {
    case 0:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;

    case 1:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;

    case 2:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;

    case 3:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      break;

    case 4:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      break;
  
    default:
      break;
  }

    if (QtdLeds > 4){
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
  }

  if (QtdLeds < 0){
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
  }

  return;

}

void getSensorTime(){

  ReturnTime = micros();
  first = true;
  sampled = true;

}

float getObjectDistance(){

  float distance = 0;

  unsigned long int currentTime = micros();


    if(sampled){

      distance = (ReturnTime - InitialTime)*340.0*0.000001/2.0; 
      //Resets and wait for response to calculate again
      sampled = false;
      calculated = true;

    }

  //Only requests a new value if 50us has passed and there is a sample, or is 
  //the first time the program is running. 
  if ((((currentTime - InitialTime) > 50) & (calculated == true)) | (first == false)){  

    digitalWrite(DistanceTrigger, HIGH); 
    InitialTime = micros();
    delayMicroseconds(15); 
    digitalWrite(DistanceTrigger, LOW);

    }

  return distance;

}