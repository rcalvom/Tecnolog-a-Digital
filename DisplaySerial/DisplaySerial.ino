#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#include "queue.h"
#include "TM1637.h"

QueueHandle_t xQueue;                   //se declara manejador de una cola de mensajes: de TaskReceive a TaskPosXY

// define tasks for Receive and Leds
void TaskControl( void *pvParameters );
void TaskReceive( void *pvParameters );

#define ON 1
#define OFF 0

#define CLK 2
#define DIO 3

unsigned char Update;

TM1637 tm1637(CLK,DIO);
