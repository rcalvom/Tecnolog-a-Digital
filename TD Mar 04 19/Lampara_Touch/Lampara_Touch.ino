#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#include "queue.h"

const int sensorPin=8;
const int ledPin=3;

// define tasks ;
void TaskLamp( void *pvParameters );
