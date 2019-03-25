//===================================================
//================== TaskSoundAlarm =======================

void TaskSoundAlarm(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  //-----------para hacer que una tarea sea periodica ----------------------------------------
    TickType_t xPreviousWakeTime;
    xPreviousWakeTime=xTaskGetTickCount(); //Ultima vez que la tarea paso del estado Blocked al estado Ready 
                                           //se hace igual al numero de ticks actuales
  //------------------------------------------------------------------------------------------

  /*
    TaskSoundAlarm: Suena la alarma
  */

    enum state_type{START};
    state_type state;
    bool Fsm_isActive=false;
    bool stBuzzer=LOW; //estado del buzzer LOW=desactivado, HIGH=activado

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=START;         //ir al estado START
    }else{  
      switch(state){
        case START:
          stBuzzer=!stBuzzer;
          digitalWrite(buzzer,stBuzzer);//activado-desctivado: periodo 200 ms
          break;    
      }
    }//end if
    vTaskDelayUntil(&xPreviousWakeTime,100/ portTICK_PERIOD_MS ); // Bloquea task de forma periodica por 200 ms                                                                             //esperar 1 segundo en el estado bloqueado                                                                                                                
  }//end for
}//end task
//===========================================================

