void setup() {
  ConfigPins();
  String string_for_dimension = "Hello String";      //strings de 12 caracteres
  xQueue=xQueueCreate(1,sizeof(String));             //se crea la cola de mensajes xQueue 
  randomSeed(analogRead(0)); //inicializar el generador de numeros aleatorios   
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);  
  while (!Serial) {
    ; // wait for serial port to connect
  }                       

  // Now set up the two task.
  xTaskCreate(
    TaskLeds1
    ,  (const portCHAR *)"Leds1"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskLeds2
    ,  (const portCHAR *)"Leds2"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );    

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}
