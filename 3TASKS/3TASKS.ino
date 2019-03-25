#include <Arduino_FreeRTOS.h>
#include <Button.h> 
#define BUTTON_PIN 2       //Connect a tactile button switch (or something similar)
#include "semphr.h"        //from Arduino pin 2 to ground.
#define PULLUP true        //To keep things simple, we use the Arduino's internal pullup resistor.
#define INVERT true                         //means the button is NOT pressed. (Assuming a normally open switch.)
#define DEBOUNCE_MS 20     //A debounce time of 20 milliseconds usually works well for tactile button switches.

   void outSerial(char y[]);
   void Task1(void *pvParameters);
   void Task2(void *pvParameters);                        //switch is closed, this is negative logic, i.e. a high state
   void Task3(void *pvParameters);
   
Button myBtn(BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);  

const int pinred = 3;
const int pingreen = 4;
const int pinblue = 5;

const int pinred2 = 6;
const int pinyellow = 7;
const int pinwhite = 8;

const int pin0 = 9;
const int pin1 = 10;

SemaphoreHandle_t Sema_E;  
SemaphoreHandle_t Sema_Q;  

void setup() {
  configPins();
  pinMode(2,OUTPUT);
  Serial.begin(9600);
  
  while(!Serial) {
    ;
  }
  Sema_E=xSemaphoreCreateBinary();
  Sema_Q=xSemaphoreCreateBinary();
  xTaskCreate(
    Task1
    ,  (const portCHAR *)"task1"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
xTaskCreate(
    Task2
    ,  (const portCHAR *)"task2"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.

xTaskCreate(
    Task3
    ,  (const portCHAR *)"task3"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}


void loop() {
  void task1();
}

void Task1(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
    enum state_type{A,B};
    state_type state;
    bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;     
      state= A;              
      outSerial("A");  
      digitalWrite(pin0,HIGH);
      digitalWrite(pin1,LOW);
    }else{
      myBtn.read();           //lee el estado del pulsador
      switch(state){
        case A:  
         if (myBtn.wasPressed()){ 
       state = B;
       digitalWrite(pin0,HIGH);
       digitalWrite(pin1,LOW);
         }
          break;
        case B:
          if (myBtn.wasPressed()){ 
          state = A;
         digitalWrite(pin0,LOW);
         digitalWrite(pin1,HIGH);
         }          
          break;
      }//end switch         
    }//end if
                                                                        
  }
}

void Task2(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
    enum state_type{Red,Green,Blue};
    state_type state;
    bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;      //activar la FSM
      state= Red;              //ir al estado Red
      outSerial("Red");       //al entrar (en) al estado Red llamar la funcion outSerial, en:outSerial("Red");
    }else{
      myBtn.read();           //lee el estado del pulsador
      switch(state){
        case Red:  
         if (myBtn.wasPressed()){
  digitalWrite(pinred,HIGH);
  digitalWrite(pingreen,LOW);
  digitalWrite(pinblue,LOW);
         }
          break;
        case Green:
          if (myBtn.wasPressed()){
  digitalWrite(pinred,LOW);
  digitalWrite(pingreen,HIGH);
  digitalWrite(pinblue,LOW);;
         }
          break;
          case Blue:
          if (myBtn.wasPressed()){
  digitalWrite(pinred,LOW);
  digitalWrite(pingreen,LOW);
  digitalWrite(pinblue,HIGH);
         }
          break;
      }//end switch         
    }//end if
    vTaskDelay(200/ portTICK_PERIOD_MS ); // Bloquea task1 por 200 ms                                                                    
  }//end for
}

void Task3(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
    enum state_type{Yellow,White,Red2};
    state_type state;
    
    bool Fsm_isActive=false;

    unsigned long timeCounter=0;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;      //activar la FSM
      state= Yellow;              //ir al estado Red
      outSerial("Yellow");       //al entrar (en) al estado Red llamar la funcion outSerial, en:outSerial("Red");
    }else{
      myBtn.read();           //lee el estado del pulsador
      switch(state){
        case Yellow:  
         if (myBtn.wasPressed()){
        //xSemaphoreGive(Sema_E);  
       digitalWrite(pinyellow,HIGH);
       digitalWrite(pinwhite,LOW);
       digitalWrite(pinred2,LOW);
         }
          break;
        case White:
          if (myBtn.wasPressed()){
         //xSemaphoreGive(Sema_E);
       digitalWrite(pinyellow,LOW);
       digitalWrite(pinwhite,HIGH);
       digitalWrite(pinred2,LOW);
         }
          break;
          case Red2:
          if (myBtn.wasPressed()){
         // xSemaphoreGive(Sema_E);            
       digitalWrite(pinyellow,LOW);
       digitalWrite(pinwhite,LOW);
       digitalWrite(pinred2,HIGH);
         }
          break;
      }//end switch         
    }//end if
    vTaskDelay(200/ portTICK_PERIOD_MS ); // Bloquea task1 por 200 ms                                                                    
  }//end for
}
void configPins(){
  pinMode(pinred,OUTPUT);
  pinMode(pingreen,OUTPUT);
  pinMode(pinblue,OUTPUT);
  pinMode(pinyellow,OUTPUT);
  pinMode(pinwhite,OUTPUT);
  pinMode(pinred2,OUTPUT);
  pinMode(pin0,OUTPUT);
  pinMode(pin1,OUTPUT);

  digitalWrite(pinred,LOW);
  digitalWrite(pingreen,LOW);
  digitalWrite(pinblue,LOW);
  digitalWrite(pinyellow,LOW);
  digitalWrite(pinwhite,LOW);
  digitalWrite(pinred2,LOW);
  digitalWrite(pin0,LOW);
  digitalWrite(pin1,LOW);
}

void outSerial(char y[]){
  Serial.println(y); 
}


