void setup() { 
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect
  } 
  pinMode(13,HIGH);

  // Now set up the two task.
  xTaskCreate(
    TaskLamp
    ,  (const portCHAR *)"Lamp"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL);

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}
