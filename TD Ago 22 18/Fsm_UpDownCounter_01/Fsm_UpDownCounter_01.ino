#include <Arduino_FreeRTOS.h>

// define task for UpDownCounter
void TaskUpDownCounter( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect
  }

  // Now set up task.
  xTaskCreate(
    TaskUpDownCounter
    ,  (const portCHAR *)"UpDownCounter"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (bytes)
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

void TaskUpDownCounter(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

/*
  UpDownCounter: 0 up to 8 down to 0, value sent by serial port
*/

    enum state_type{A,B,C};
    state_type state;
    
    bool FsmActive=false;
    byte y;

  for (;;) // A Task shall never return or exit.
  { 
    if (FsmActive==false){
      FsmActive=true; //activar la FSM
      y=0;            //al ejecutar la transicion inicial de entrada a la FSM inicializar y en 0, {y=0}
      state=A;        //ir al estado A
      outy(y);        //al entrar (en) al estado A llamar la funcion outy, en:outy(y);
    }else{
      switch(state){
        case A:
          state=B;  //ir a estado B
          y++;      //al entrar (en) al estado B incrementar y, en:y++; 
          outy(y);  //al entrar (en) al estado B llamar la funcion outy, en:outy(y); 
          break;
        case B:
          if(y<8){
            state=B; //ir a estado B
            y++;     //al entrar (en) al estado B incrementar y, en:y++;
            outy(y); //al entrar (en) al estado B llamar la funcion outy, en:outy(y);
          }else{
            state=C; //ir a estado C
            y--;     //al entrar (en) al estado C decrementar y, en:y--;
            outy(y); //al entrar (en) al estado C llamar la funcion outy, en:outy(y);
          }
          break;
        case C:
        if(y>1){
          state=C;  //ir al estado C
          y--;      //al entrar (en) al estado C decrementar y, en:y--;
          outy(y);  //al entrar (en) al estado C llamar la funcion outy, en:outy(y);
        }else{
          y--;      //al hacer la transicion hacia A hacer esta accion: {y--}
          state=A;  //ir al estado A 
          outy(y);  //al entrar (en) a A ejecutar esta accion: llamar a la funcion outy, en:out(y)
       
        }
        break;     
      }//end switch        
    }//end if

    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second

  }//end for
}//end task

//**********************************************************
//****************** Functions *****************************

void outy(byte y){
  Serial.println(y); 
}
//***********************************************************

