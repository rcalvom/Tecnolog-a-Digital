//enviar un dato de 1 byte a pines de salida: ejemplo contador de 0 a 255
#include <Arduino_FreeRTOS.h>

//---------CONSTANTS----------------------
// set output pins numbers:
const int outPins[8]={5,8,9,12,4,6,7,11}; //outPins[0]:least significant bit; outPins[7]:most significant bit; 
int sensorPin = A0;    // select the input pin for the potentiometer

//--------VARIABLES-----------------------
//struct for raw data byte
struct DATARAW
{
  byte b0: 1;
  byte b1: 1;
  byte b2: 1;
  byte b3: 1;
  byte b4: 1;
  byte b5: 1;
  byte b6: 1;
  byte b7: 1;
};
//union for output data byte
union DATAO
{
  DATARAW rawdata;
  byte value;
};

DATAO dout; //dout instancia de DATAO

// define tasks for TaskCounter
void TaskCounter( void *pvParameters );



