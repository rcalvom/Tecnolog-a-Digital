void setup() { 
  tm1637.set();
  tm1637.init();
  Timer1.initialize(500000);//timing for 500ms
  //Timer1.initialize(250000);//timing for 250ms
  //Timer1.initialize(100000);//timing for 100ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);  
  while (!Serial) {
    ; // wait for serial port to connect
  }      

  // Now set up the two task.
  xTaskCreate(
    TaskCounter
    ,  (const portCHAR *)"Counter"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL);

  xTaskCreate(
    TaskButtons
    ,  (const portCHAR *)"Buttons"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL);    

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}
