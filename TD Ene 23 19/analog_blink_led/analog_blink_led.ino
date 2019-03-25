//valor analogo cambia la frecuencia de encendido de un led
#include <Arduino_FreeRTOS.h>

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED

// define tasks for TaskBlinkControl
void TaskBlinkControl( void *pvParameters );



