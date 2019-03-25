void setup() {
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,LOW); //silence
  pinMode(AlarmLed,OUTPUT);
  digitalWrite(AlarmLed,LOW); //apagado
  pinMode(RED,OUTPUT);
  digitalWrite(RED,HIGH);
  pinMode(GREEN,OUTPUT);
  digitalWrite(GREEN,HIGH);
  pinMode(BLUE,OUTPUT);
  digitalWrite(BLUE,HIGH);

  pinMode(SW_ON_OFF,INPUT_PULLUP);
  
  tm1637.set();
  tm1637.init();
  Timer1.initialize(500000);//timing for 500ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR
  randomSeed(0);

  // Now set up the two task.
  xTaskCreate(
    TaskClock
    ,  (const portCHAR *)"Clock"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL);

  xTaskCreate(
    TaskChangeTime
    ,  (const portCHAR *)"ChangeTime"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );    

  xTaskCreate(
    TaskChangeAlarm
    ,  (const portCHAR *)"ChangeAlarm"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );        

  xTaskCreate(
    TaskLedRGB
    ,  (const portCHAR *)"ChangeLed"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  2  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}
