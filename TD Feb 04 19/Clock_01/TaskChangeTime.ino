//===================================================
//================== TaskChangeTime =======================

void TaskChangeTime(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  //-----------para hacer que una tarea sea periodica ----------------------------------------
    TickType_t xPreviousWakeTime;
    xPreviousWakeTime=xTaskGetTickCount(); //Ultima vez que la tarea paso del estado Blocked al estado Ready 
                                           //se hace igual al numero de ticks actuales
  //------------------------------------------------------------------------------------------

  /*
    TaskChangeTime: Cambio de la hora actual
  */

    enum state_type{START,DELAY1,AGAIN,DELAY2};
    state_type state;
    int contador=0;
    bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=START;         //ir al estado START
    }else{  
      if(BtnTime.isPressed()==true){ //realizar solo si BtnTime se encuentra oprimido        
        switch(state){
          case START: //Acciones si el BtnHour o el BtnMin fue pulsado
            if(BtnHour.wasPressed()==true){
              Update = ON;            
              if (hour<23) hour++;
              else hour=0;
              state=DELAY1;     
            }else if(BtnMin.wasPressed()==true){
              Update = ON;            
              if (minute<59) minute++;
              else minute=0;
              state=DELAY1;     
            }
            break; 
          case DELAY1: //delay antes de empezar repeticion de incrementos (100 + 3*100=400ms)
            contador++;
            if (contador==3){
              contador=0;
              state=AGAIN;             
            }
            break;
          case AGAIN: //repetir mientras boton BtnHour o  el boton BtnMin estan oprimido
            if(BtnHour.isPressed()==true){
              Update = ON;     
              if (hour<23) hour++;
              else hour=0;
              state=DELAY2; 
            }else if(BtnMin.isPressed()==true){
              Update = ON;            
              if (minute<59) minute++;
              else minute=0;
              state=DELAY2;                 
            }else{        
              state=START; //si ninguno esta oprimido regresar a START     
            }             
            break;  
          case DELAY2: //delay del autoincremento (100 + 2*100 = 300ms)
            contador++;
            if (contador==2){
              contador=0;
              state=AGAIN;             
            }
            break;                   
        }//end switch  
      }       
    }//end if
    vTaskDelayUntil(&xPreviousWakeTime,100/ portTICK_PERIOD_MS ); // Bloquea task1 de forma periodica por 100 ms                                                                             //esperar 1 segundo en el estado bloqueado                                                                                                                
  }//end for
}//end task
//===========================================================

