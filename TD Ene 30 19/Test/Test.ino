#include <Arduino_FreeRTOS.h>
#include "TM1637.h"  //Grove_4Digital_Display-master

#define CLK 2//pins definitions for TM1637 and can be changed to other ports
#define DIO 3
TM1637 tm1637(CLK,DIO); //crear objeto tm1637

//int8_t data[] = {29,33,34,35};
//int8_t data[] = {28,0,28,10};
int8_t data[] = {13,0,23,14};
float num = 9385;




