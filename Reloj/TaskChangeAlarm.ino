//===================================================
//================== TaskChangeAlarm =======================

void TaskChangeAlarm(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  //-----------para hacer que una tarea sea periodica ----------------------------------------
    TickType_t xPreviousWakeTime;
    xPreviousWakeTime=xTaskGetTickCount(); //Ultima vez que la tarea paso del estado Blocked al estado Ready 
                                           //se hace igual al numero de ticks actuales
  //------------------------------------------------------------------------------------------

  /*
    TaskChangeAlarm: Cambio de la hora de la alarma
  */

    enum state_type{Start,Delay1,Delay2,Test1};
    state_type state;
    int contador=0;
    bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=Start;         //ir al estado Start
    }else{  
      if(BtnAlarm.isPressed()==true){ 
        switch(state){
          case Start:
            if(BtnHour.wasPressed()==true){    
              if (hourAlarm<23) hourAlarm++;
              else hourAlarm=0;
              state=Delay1;     
            }else if(BtnMin.wasPressed()==true){
              Update = ON;            
              if (minuteAlarm<59) minuteAlarm++;
              else minuteAlarm=0;
              state=Delay1;     
            }
            break; 
          case Delay1:
            contador++;
            if (contador==3){
              contador=0;
              state=Test1;             
            }
            break;
          case Test1:
            if(BtnHour.isPressed()==true){
              Update = ON;     
              if (hourAlarm<23) hourAlarm++;
              else hourAlarm=0;
              state=Delay2; 
            }else if(BtnMin.isPressed()==true){
              Update = ON;            
              if (minuteAlarm<59) minuteAlarm++;
              else minuteAlarm=0;
              state=Delay2;                 
            }else{        
              state=Start;     
            }             
            break;  
          case Delay2:
            contador++;
            if (contador==2){
              contador=0;
              state=Test1;             
            }
            break;                   
        }//end switch  
      }       
    }//end if
    vTaskDelayUntil(&xPreviousWakeTime,100/ portTICK_PERIOD_MS ); // Bloquea task de forma periodica por 100 ms                                                                             //esperar 1 segundo en el estado bloqueado                                                                                                                
  }//end for
}//end task
//===========================================================

