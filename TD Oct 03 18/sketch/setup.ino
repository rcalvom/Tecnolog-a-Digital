// the setup function runs once when you press reset or power the board
void setup() {
  xBinSem_E=xSemaphoreCreateBinary();     //se crea el semáforo
  byte data[3];
  xQueue=xQueueCreate(1,sizeof(data));       //se crea la cola de mensajes xQueue: capacidad 1 mensaje de 3 bytes 
  byte data1[2];
  xQueue1=xQueueCreate(1,sizeof(data1));       //se crea la cola de mensajes xQueue: capacidad 1 mensaje de 2 bytes 
   
  
  randomSeed(analogRead(0)); //inicializar el generador de numeros aleatorios
     
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);  
  while (!Serial) {
    ; // wait for serial port to connect
  }      
  Serial.flush();                 

  // Now set up the two task.
  xTaskCreate(
    TaskTransmit
    ,  (const portCHAR *)"Transmit"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );
  xTaskCreate(
    TaskReceive
    ,  (const portCHAR *)"Receive"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );
  xTaskCreate(
    TaskPosXY
    ,  (const portCHAR *)"PosX"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );    

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}
