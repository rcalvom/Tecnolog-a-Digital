//===================================================
//================== TaskCounter =======================

void TaskCounter(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  //-----------para hacer que una tarea sea periodica ----------------------------------------
    TickType_t xPreviousWakeTime;
    xPreviousWakeTime=xTaskGetTickCount(); //Ultima vez que la tarea paso del estado Blocked al estado Ready 
                                           //se hace igual al numero de ticks actuales
  //------------------------------------------------------------------------------------------  
  
  /*
    TaskCounter: contador de 0 a 255;
  */  
    
  bool Fsm_isActive=false;
  byte count;           //variable contadora

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      count=0;
    }else{
      dout.value=/*count*/154;
      Serial.println(dout.value);
      writeData2Pins(outPins);
      count++;
    }//end if
    vTaskDelayUntil(&xPreviousWakeTime,200/portTICK_PERIOD_MS ); //tarea periodica: periodo 200 ms                                                                                                        
  }//end for
}//end task
//===========================================================


