#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#include "queue.h"

//SemaphoreHandle_t xBinSem_E,xBinSem_Q;  //se declara manejador de un un semáforo
QueueHandle_t xQueue;                   //se declara manejador de una cola de mensajes


// define tasks for Leds1 and Leds2
void TaskLeds1( void *pvParameters );
void TaskLeds2( void *pvParameters );

void outSerial(char y[]){
  Serial.println(y); 
}

void ConfigPins(){
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
}

void RedON(bool state){
  digitalWrite(2,state);
}

void GreenON(bool state){
  digitalWrite(3,state);
}

void YellowON(bool state){
  digitalWrite(5,state);
}

void BlueON(bool state){
  digitalWrite(4,state);
}

//***********************************************************

