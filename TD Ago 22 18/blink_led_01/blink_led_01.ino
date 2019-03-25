#include <Arduino_FreeRTOS.h>

// define one task
void TaskBlink( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {

  // Now set up task.
  xTaskCreate(
    TaskBlink
    ,  (const portCHAR *)"Blink"  // A descriptive name for the task. Not used by FreeRTOS in any way. 
    ,  128  // Stack size (bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

//****************************************************************************************
//****************** Tasks ***************************************************************

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
*/

  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}
//**************************************************************************************

