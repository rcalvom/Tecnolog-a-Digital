#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#include "queue.h"

const int red = 2;
const int green = 3;
const int blue = 4;
const int yellow = 5;
const int i0 = 10;
const int i1 = 9;
const int i2 = 8;
const int i3 = 7;


SemaphoreHandle_t xBinSem_E, xBinSem_Q; 
QueueHandle_t xQueue;

void TaskLeds1( void *pvParameters );
void TaskLeds2( void *pvParameters );

struct DATARAW {
  byte b0: 1;
  byte b1: 1;
  byte b2: 1;
  byte b3: 1;
};

union DATAO {
  DATARAW rawdata;
  byte value;
};

DATAO count;

void setup() {

  randomSeed(analogRead(0));
  ConfigPins();
  
  xBinSem_E = xSemaphoreCreateBinary();
  xBinSem_Q = xSemaphoreCreateBinary();
  xQueue = xQueueCreate(1, sizeof(long));

  Serial.begin(9600);

  while (!Serial) {
    
  }

  xTaskCreate(
    TaskLeds1
    ,  (const portCHAR *)"Leds1"
    ,  128  
    ,  NULL
    ,  1 
    ,  NULL );

  xTaskCreate(
    TaskLeds2
    ,  (const portCHAR *)"Leds2"   
    ,  128  
    ,  NULL
    ,  1 
    ,  NULL );
    
}

void loop(){
  
}

void TaskLeds1(void *pvParameters){
  
  (void) pvParameters;
  
  enum state_type {Red, Green};
  state_type state;

  bool Fsm_isActive = false;

  unsigned long timeCounter = 0;
  unsigned long valueToSend;

  while(true){
    if (Fsm_isActive == false){
      Fsm_isActive = true;    
      timeCounter = 0;        
      state = Red;            
      outSerial("Red");       
      RedON(HIGH);
      GreenON(LOW);
    }else{
      switch (state){
        case Red:
          timeCounter++;         
          if (timeCounter >= 2){ 
            state = Green;
            valueToSend = random(0, 15);       
            xQueueSendToBack(xQueue, &valueToSend, 0); 
            xSemaphoreGive(xBinSem_E);               
            timeCounter = 0;     
            outSerial("Green"); 
            RedON(LOW);
            GreenON(HIGH);
          }
          break;
        case Green:
          xSemaphoreTake(xBinSem_Q, portMAX_DELAY);
          state = Red;
          outSerial("Red");
          RedON(HIGH);
          GreenON(LOW);
          break;
      }
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS ); 
  }
}

void TaskLeds2(void *pvParameters){
  
  (void) pvParameters;
  unsigned long receivedValue;

  enum state_type {Blue, Yellow};
  state_type state;

  bool Fsm_isActive = false;

  unsigned long timeCounter;

  while (true){
    if (Fsm_isActive == false) {
      Fsm_isActive = true;
      state = Blue;
      outSerial("Blue");
      BlueON(HIGH);
      YellowON(LOW);
    }else{
      switch (state) {
        case Blue:
          xSemaphoreTake(xBinSem_E, portMAX_DELAY);
          xQueueReceive(xQueue, &receivedValue, 0);
          timeCounter = receivedValue;
          count.value = timeCounter;
          writeCount();
          state = Yellow;
          Serial.println(timeCounter);
          writeCount();
          outSerial("Yellow");
          BlueON(LOW);
          YellowON(HIGH);
          break;
        case Yellow:
          timeCounter++;
          Serial.println(timeCounter);
          count.value = timeCounter;
          writeCount();
          if (timeCounter >= 15) {
            xSemaphoreGive(xBinSem_Q);
            state = Blue;
            outSerial("Blue");
            BlueON(HIGH);
            YellowON(LOW);
          }
          break;
      }
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS );
  }
}

void outSerial(char y[]) {
  Serial.println(y);
}

void ConfigPins() {
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(i0, OUTPUT);
  pinMode(i1, OUTPUT);
  pinMode(i2, OUTPUT);
  pinMode(i3, OUTPUT);
  count.value = 0;
}

void RedON(bool state) {
  digitalWrite(red, state);
}

void BlueON(bool state) {
  digitalWrite(blue, state);
}

void GreenON(bool state) {
  digitalWrite(green, state);
}

void YellowON(bool state) {
  digitalWrite(yellow, state);
}

void writeCount() {
  digitalWrite(i0,count.rawdata.b0);
  digitalWrite(i1,count.rawdata.b1);
  digitalWrite(i2,count.rawdata.b2);
  digitalWrite(i3,count.rawdata.b3);
}

