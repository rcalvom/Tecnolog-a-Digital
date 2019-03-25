// the setup function runs once when you press reset or power the board
void setup() {

  tm1637.set();
  tm1637.init();
  tm1637.point(true);
  
  String data = "9999";
  xQueue=xQueueCreate(1,sizeof(data));       //se crea la cola de mensajes xQueue: capacidad 1 mensaje de 4 bytes    
     
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);  
  while (!Serial) {
    ; // wait for serial port to connect
  }      
  Serial.flush();                 

  // Now set up the two task.
  xTaskCreate(
    TaskReceive
    ,  (const portCHAR *)"Receive"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );
  xTaskCreate(
    TaskControl
    ,  (const portCHAR *)"Control"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );    

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}
