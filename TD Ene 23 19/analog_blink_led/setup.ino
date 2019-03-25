// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(ledPin, OUTPUT); //pin del led como salida
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);  
  while (!Serial) {
    ; // wait for serial port to connect
  }      
  Serial.flush();                 

  // Now set up task
  xTaskCreate(
    TaskBlinkControl
    ,  (const portCHAR *)"BlinkControl"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );    

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}
