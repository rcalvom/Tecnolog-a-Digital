#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#include "queue.h"

//SemaphoreHandle_t xBinSem_E,xBinSem_Q;  //se declara manejador de un un semáforo
QueueHandle_t xQueue;                   //se declara manejador de una cola de mensajes


// define tasks for Leds1 and Leds2
void TaskLeds1( void *pvParameters );
void TaskLeds2( void *pvParameters );


// the setup function runs once when you press reset or power the board
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

void loop()
{
  // Empty. Things are done in Tasks.
}

//****************************************************
//****************** Tasks ***************************

//===================================================
//================== TaskLeds1 =======================

void TaskLeds1(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
  /*
    TaskLeds1: Manejo de leds Rojo y Verde
  */

    enum state_type{Red,Green,Yellow};
    state_type state; 
    bool Fsm_isActive=false;
    unsigned long timeCounter=0,r;
    String stringToSend;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;      //activar la FSM
      state=Red;              //ir al estado Red
      stringToSend="Red_m";
      timeCounter=0;          //inicializar el contador de tiempo 
      xQueueSendToBack(xQueue,&stringToSend,0); //colocar mensaje al final de la cola            
      outSerial("Red");       //al entrar (en) al estado Red llamar la funcion outSerial, en:outSerial("Red");
      RedON(HIGH);
      YellowON(LOW);
      GreenON(LOW);
    }else{
      switch(state){
        case Red:             
          timeCounter++;         //Incrementar contador de Tiempo 
          if(timeCounter>=2){    //Si han pasado 2 o mas segundos:  
            r=random(0,2);
            if(r==0){                                            
              state=Green;           //ir al estado Green
              stringToSend="Green_m";//mensaje a enviar
              xQueueSendToBack(xQueue,&stringToSend,0); //colocar mensaje al final de la cola 
              timeCounter=0;       //hacer un reset del contador de tiempo        
              outSerial("Green");
              RedON(LOW);
              YellowON(LOW);
              GreenON(HIGH);
            }else{     
              state=Yellow;           //ir al estado Yellow
              stringToSend="Yellow_m";//mensaje a enviar
              xQueueSendToBack(xQueue,&stringToSend,0); //colocar mensaje al final de la cola  
              timeCounter=0;       //hacer un reset del contador de tiempo        
              outSerial("Yellow");
              RedON(LOW);
              YellowON(HIGH);
              GreenON(LOW);
            }            
          }
          break;
        case Green:
          timeCounter++;                //Incrementar contador de Tiempo 
          if(timeCounter>=5){           //Si han pasado 5 o mas segundos:         
            state=Red;                  //ir al estado Red
            stringToSend="Red_m";       //mensaje a enviar
            xQueueSendToBack(xQueue,&stringToSend,0); //colocar mensaje al final de la cola                    
            timeCounter=0;              //hacer un reset del contador de tiempo
            outSerial("Red");           //al entrar (en) al estado Red llamar la funcion outSerial, en:outSerial("Red");          
            RedON(HIGH);
            YellowON(LOW);
            GreenON(LOW);
          }
          break;
        case Yellow:
          timeCounter++;                //Incrementar contador de Tiempo 
          if(timeCounter>=5){           //Si han pasado 2 o mas segundos:              
            state=Red;                  //ir al estado Red
            stringToSend="Red_m";       //mensaje a enviar
            xQueueSendToBack(xQueue,&stringToSend,0); //colocar mensaje al final de la cola               
            timeCounter=0;              //hacer un reset del contador de tiempo
            outSerial("Red");           //al entrar (en) al estado Red llamar la funcion outSerial, en:outSerial("Red"); 
            RedON(HIGH);
            YellowON(LOW);
            GreenON(LOW);
          }
          break;    
      }//end switch         
    }//end if
    vTaskDelay(1000 / portTICK_PERIOD_MS ); // //esperar 1 segundo en el estado bloqueado                                                                     
  }//end for
}//end task

//===================================================
//================== TaskLeds2 =======================

void TaskLeds2(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  /*
    TaskLeds2: Manejo de leds Azul y Amarillo
  */
  String stringReceived;  //mensaje recibido
  portBASE_TYPE xStatus;  //estado de la cola de mensajes
  
  enum state_type{Blue};
  state_type state;
  bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=Blue;
      outSerial("Blue");
      BlueON(HIGH);
    }else{ 
      switch(state){
        case Blue:
        
          do{
            xStatus=xQueueReceive(xQueue,&stringReceived,0);   //recibir el mensaje al principio de la cola, si no esta vacia          
          }while (xStatus != pdPASS);                          //mientras la cola no tenga mensaje repetir
          
          if(stringReceived.equals("Red_m")){
            Serial.println("RED_LED");                         
          }else if (stringReceived.equals("Green_m")) {
            Serial.println("Green_LED");  
          }else{
            Serial.println("Yellow_LED");   
          }
          state=Blue;
          break;
      }//end switch
    }//end if
    vTaskDelay(100 / portTICK_PERIOD_MS );         //esperar 1 segundo en el estado bloqueado                                                                                                                
  }//end for
}//end task
//===========================================================

//**********************************************************
//****************** Functions *****************************

void outSerial(char y[]){
  Serial.println(y); 
}

void ConfigPins(){
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
}

void RedON(bool state){
  digitalWrite(2,state);
}

void GreenON(bool state){
  digitalWrite(3,state);
}

void YellowON(bool state){
  digitalWrite(5,state);
}

void BlueON(bool state){
  digitalWrite(4,state);
}

//***********************************************************

