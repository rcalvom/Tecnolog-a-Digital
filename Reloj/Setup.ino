void setup() {
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,LOW); //silence
  pinMode(AlarmLed,OUTPUT);
  digitalWrite(AlarmLed,LOW); //apagado
  pinMode(Red,OUTPUT);
  digitalWrite(Red,LOW);
  pinMode(Green,OUTPUT);
  digitalWrite(Green,LOW);
  pinMode(Blue,OUTPUT);
  digitalWrite(Blue,LOW);

  pinMode(SW_ON_OFF,INPUT_PULLUP);
  
  tm1637.set();
  tm1637.init();
  Timer1.initialize(500000);//timing for 500ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);  
  while (!Serial) {
    ; // wait for serial port to connect
  }      

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
    TaskSoundAlarm
    ,  (const portCHAR *)"ChangeAlarm"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );  

  xTaskCreate(
    TaskLed
    ,  (const portCHAR *)"Led"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL ); 

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}
