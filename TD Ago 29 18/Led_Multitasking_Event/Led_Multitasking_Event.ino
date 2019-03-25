#include <Arduino_FreeRTOS.h>
#include "semphr.h"

SemaphoreHandle_t xBinSem_E;  //se declara un semáforo


// define tasks for Leds1 and Leds2
void TaskLeds1( void *pvParameters );
void TaskLeds2( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  init();
  xBinSem_E=xSemaphoreCreateBinary();   //se crea el semáforo
  
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
    ,  2  // Priority, with 3 being the highest, and 0 being the lowest.
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
  //-----------para hacer que una tarea sea periodica ----------------------------------------
    TickType_t xPreviousWakeTime;
    xPreviousWakeTime=xTaskGetTickCount(); //Ultima vez que la tarea paso del estado Blocked al estado Ready 
                                           //se hace igual al numero de ticks actuales
  //------------------------------------------------------------------------------------------

  /*
    TaskLeds1: Manejo de leds Rojo y Verde
  */

    enum state_type{Red,Green};
    state_type state;
    
    bool Fsm_isActive=false;

    unsigned long timeCounter;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;      //activar la FSM
      state=Red;              //ir al estado Red
      timeCounter=0;          //inicializar el contador de tiempo
      outSerial("Red");
      red(HIGH);
      green(LOW);//al entrar (en) al estado Red llamar la funcion outSerial, en:outSerial("Red");
    }else{
      switch(state){
        case Red:             
          timeCounter++;         //Incrementar contador de Tiempo 
          if(timeCounter>=4){    //Si han pasado 4 o mas segundos:
            state=Green;         //ir al estado Green
            timeCounter=0;       //hacer un reset del contador de tiempo
            outSerial("Green");
            red(LOW);
            green(HIGH);//al entrar (en) al estado Green llamar la funcion outSerial, en:outSerial("Green"); 
          }
          break;
        case Green:
          timeCounter++;                //Incrementar contador de Tiempo 
          if(timeCounter>=2){           //Si han pasado 2 o mas segundos:
            xSemaphoreGive(xBinSem_E);  //se da el semaforo
            state=Red;                  //ir a estado Red
            timeCounter=0;              //hacer un reset del contador de tiempo
            outSerial("Red");
            red(HIGH);
            green(LOW);//al entrar (en) al estado Red llamar la funcion outSerial, en:outSerial("Red"); 
          }
          break; 
      }//end switch         
    }//end if
    vTaskDelay(1000 / portTICK_PERIOD_MS ); // Bloquea task1, e indica con que periodo debe ser movida  
                                                                    // de nuevo del estado Blocked al estado Ready
  }//end for
}//end task

//===================================================
//================== TaskLeds2 =======================

void TaskLeds2(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  //-----------para hacer que una tarea sea periodica  ---------------------------------------
    TickType_t xPreviousWakeTime;
    xPreviousWakeTime=xTaskGetTickCount(); //Ultima vez que la tarea paso del estado Blocked al estado Ready 
                                           //se hace igual al numero de ticks actuales
  //-------------------------------------------------------------------------------------------

  /*
    TaskLeds2: Manejo de leds Azul y Amarillo
  */

    enum state_type{Blue,Yellow};
    state_type state;
    
    bool Fsm_isActive=false;

    unsigned long timeCounter;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=Blue;         //ir al estado Blue
      timeCounter=0;      //inicializar el contador de tiempo
      outSerial("Blue");  //al entrar (en) al estado Blue llamar la funcion outSerial, en:outSerial("Blue");
      blue(HIGH);
      yellow(LOW);
    }else{
      switch(state){
        case Blue:
          timeCounter++;          //Incrementar contador de Tiempo 
          if(timeCounter>=3){     //Si han pasado 3 o mas segundos:
            state=Yellow;         //ir al estado Yellow
            timeCounter=0;        //hacer un reset del contador de tiempo.
            outSerial("Yellow");  //al entrar (en) al estado Yellow llamar la funcion outSerial, en:outSerial("Yellow");
            blue(LOW);
            yellow(HIGH);
          }
          break;
        case Yellow:
            xSemaphoreTake(xBinSem_E,portMAX_DELAY);  //se toma el semáforo
            state=Blue;                               //ir a estado Blue
            outSerial("Blue");
            blue(HIGH);
            yellow(LOW);//al entrar (en) al estado Blue llamar la funcion outSerial, en:outSerial("Blue");           
          break;  
      }//end switch         
    }//end if
    vTaskDelayUntil(&xPreviousWakeTime,pdMS_TO_TICKS(1000) ); // Bloquea task1, e indica con que periodo debe ser movida  
                                                              // de nuevo del estado Blocked al estado Ready                                                        
  }//end for
}//end task
//===========================================================

//**********************************************************
//****************** Functions *****************************

void outSerial(char y[]){
  Serial.println(y); 
}

void init(){ 
  pinMode(4,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
}

void red(bool state){
  digitalWrite(4,state);
}
void blue(bool state){
  digitalWrite(8,state);
}
void yellow(bool state){
  digitalWrite(10,state);
}
void green(bool state){
  digitalWrite(6,state);
}
//***********************************************************

