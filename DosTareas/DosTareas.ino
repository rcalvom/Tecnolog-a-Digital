#include <Arduino_FreeRTOS.h>
#include "semphr.h"

const int red1 = 6;
const int blue1 = 7;
const int green1 = 8;
const int red2 = 10;
const int yellow2 = 11;
const int white2 = 12;

#define BUTTON_PIN 2                                  
#define PULLUP true        
#define INVERT true                   
#define DEBOUNCE_MS 20

SemaphoreHandle_t xBinSem_E;
SemaphoreHandle_t xBinSem_Q;

void Leds1( void *pvParameters );
void Leds2( void *pvParameters );

void setup() {
  ConfigPins();
  xBinSem_E=xSemaphoreCreateBinary();
  xBinSem_Q=xSemaphoreCreateBinary();

  Serial.begin(9600);
  
  while (!Serial) {
    ;
  }
  
  xTaskCreate(
    Leds1
    ,  (const portCHAR *)"Leds1"   
    ,  128  
    ,  NULL
    ,  1  
    ,  NULL );

  xTaskCreate(
    Leds2
    ,  (const portCHAR *)"Leds2"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );

}

void loop() {

}

void Leds1(void *pvParameters){  
  (void) pvParameters;
  
   TickType_t xPreviousWakeTime;
   xPreviousWakeTime=xTaskGetTickCount();

   enum state_type{Red,Blue,Green};
   state_type state;

   bool Fsm_isActive=false;
   unsigned long timeCounter;
   int cycles;

   while(true){
      if (Fsm_isActive==false){
        Fsm_isActive=true;      
        state=Red;              
        outSerial("Red");
        ONRed1(HIGH);
        ONBlue1(LOW);
        ONGreen1(LOW);
        cycles=0;
    }else{
      switch(state){
        case Red:  
        timeCounter++;
        if(timeCounter>=2){
            state=Blue;
            outSerial("Blue");
            cycles++;
            ONRed1(LOW);
            ONBlue1(HIGH);
            ONGreen1(LOW);
            timeCounter=0;
            if(cycles==3){
             xSemaphoreGive(xBinSem_Q); 
            }
        }
        break;
        case Blue:
          timeCounter++;          
          if(timeCounter>=2){    
            state=Green;         
            timeCounter=0;        
            outSerial("Green");  
            ONRed1(LOW);
            ONBlue1(LOW);
            ONGreen1(HIGH);
          }
        break;
        case Green:
          if(cycles < 5){
            timeCounter++;
            if(timeCounter>=2){
              timeCounter=0;
              state=Blue;
              outSerial("Blue");
              cycles++;
              ONRed1(LOW);
              ONBlue1(HIGH);
              ONGreen1(LOW);
              timeCounter=0;
              if(cycles==3){
                xSemaphoreGive(xBinSem_Q); 
              }
            }
          }else{
              xSemaphoreTake(xBinSem_E,portMAX_DELAY);
              state=Red;         
              timeCounter=0;
              cycles=0;       
              outSerial("Red");
              ONRed1(HIGH);
              ONBlue1(LOW);
              ONGreen1(LOW);  
          }
        break;
      }        
    }
    vTaskDelay(1000/ portTICK_PERIOD_MS ); 
  }  
}

void Leds2(void *pvParameters){
  (void) pvParameters;

   TickType_t xPreviousWakeTime;
   xPreviousWakeTime=xTaskGetTickCount();

   enum state_type{Red,Yellow,White};
   state_type state;

   bool Fsm_isActive=false;
   unsigned long timeCounter;
   int cycles;

   while(true){
      if (Fsm_isActive==false){
        Fsm_isActive=true;      
        state=Red;              
        outSerial("Red");
        ONRed2(HIGH);
        ONYellow2(LOW);
        ONWhite2(LOW);
        cycles=0;
    }else{
      switch(state){
        case Red:  
          xSemaphoreTake(xBinSem_Q,portMAX_DELAY);
          timeCounter=0;
          state=Yellow;
          outSerial("Yellow");
          cycles++;
          ONRed2(LOW);
          ONYellow2(HIGH);
          ONWhite2(LOW);
        break;
        case Yellow:
          timeCounter++;          
          if(timeCounter>=1){    
            state=White;         
            timeCounter=0;        
            outSerial("White");  
            ONRed2(LOW);
            ONYellow2(LOW);
            ONWhite2(HIGH);
          }
        break;
        case White:
          if(cycles == 10){
              xSemaphoreGive(xBinSem_E);
              timeCounter=0;
              state=Red;
              outSerial("Red");
              ONRed2(HIGH);
              ONYellow2(LOW);
              ONWhite2(LOW);
              cycles=0;  
          }else{
            timeCounter++;
            if(timeCounter>=1){     
              state=Yellow;    
              timeCounter=0;
              outSerial("Yellow");
              cycles++;
              ONRed2(LOW);
              ONYellow2(HIGH);
              ONWhite2(LOW);
            }
          }
        break;
      }        
    }
    vTaskDelay(1000/ portTICK_PERIOD_MS );    
  }  
}


void ConfigPins(){
  pinMode(red1,OUTPUT);
  pinMode(blue1,OUTPUT);
  pinMode(green1,OUTPUT);  
  pinMode(red2,OUTPUT);
  pinMode(yellow2,OUTPUT);
  pinMode(white2,OUTPUT);
}

void outSerial(char y[]){
  Serial.println(y); 
}

void ONRed1(bool state){
  digitalWrite(red1,state);
}

void ONBlue1(bool state){
  digitalWrite(blue1,state);
}

void ONGreen1(bool state){
  digitalWrite(green1,state);
}

void ONRed2(bool state){
  digitalWrite(red2,state);
}

void ONYellow2(bool state){
  digitalWrite(yellow2,state);
}

void ONWhite2(bool state){
  digitalWrite(white2,state);
}
