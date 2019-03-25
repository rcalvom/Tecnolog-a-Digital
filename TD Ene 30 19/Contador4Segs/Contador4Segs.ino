//contador display 4 segs
#include <Arduino_FreeRTOS.h>
#include "TM1637.h"  //Grove_4Digital_Display-master

#define CLK 2//pins definitions for TM1637 and can be changed to other ports
#define DIO 3
TM1637 tm1637(CLK,DIO); //crear objeto tm1637

// define tasks for TaskCounter
void TaskCounter( void *pvParameters );



