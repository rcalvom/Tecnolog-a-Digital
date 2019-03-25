// the setup function runs once when you press reset or power the board
void setup() {
  byte x[2];                              //referencia para dimensionar tamaño de mensaje
  xQueue=xQueueCreate(1,sizeof(x));       //se crea la cola de mensajes xQueue: capacidad 1 mensaje de 2 bytes  

  //config output pins:
  //pinMode(redLedPin, OUTPUT);             //led rojo
  //pinMode(greenLedPin, OUTPUT);           //led verde
  //pinMode(blueLedPin, OUTPUT);            //led azul
  
  randomSeed(analogRead(0)); //inicializar el generador de numeros aleatorios
     
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);  
  while (!Serial) {
    ; // wait for serial port to connect
  }                       

  // Now set up the two task.
  xTaskCreate(
    TaskReceive
    ,  (const portCHAR *)"Receive"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskColors
    ,  (const portCHAR *)"Colors"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );    

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}
