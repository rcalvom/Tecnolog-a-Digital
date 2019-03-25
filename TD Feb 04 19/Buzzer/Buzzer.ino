#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#include "queue.h"

const int buzzer = 9; //buzzer to arduino pin 9

// define tasks 

void TaskSoundAlarm( void *pvParameters );

