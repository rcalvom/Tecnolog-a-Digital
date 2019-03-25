#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#include "queue.h"

SemaphoreHandle_t xBinSem_E,xBinSem_Q;  //se declara manejador de un un semáforo
QueueHandle_t xQueue;                   //se declara manejador de una cola de mensajes

//led pins:
const int redLedPin    = 12;      // the pin that the red led is attached to
const int greenLedPin  = 11;      // the pin that the green led is attached to
const int blueLedPin   = 10;      // the pin that the blue led is attached to

// define tasks for Receive and Leds
void TaskReceive( void *pvParameters );
void TaskColors( void *pvParameters );
