#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#include "queue.h"

SemaphoreHandle_t xBinSem_E,xBinSem_Q;  //se declara manejador de un un semáforo
QueueHandle_t xQueue;                   //se declara manejador de una cola de mensajes: de TaskReceive a TaskPosXY
QueueHandle_t xQueue1;                  //se declara manejador de una cola de mensajes: de TaskPosXY a TaskTransmit

// define tasks for Receive and Leds
void TaskControl( void *pvParameters );
void TaskTransmit( void *pvParameters );
void TaskReceive( void *pvParameters );


