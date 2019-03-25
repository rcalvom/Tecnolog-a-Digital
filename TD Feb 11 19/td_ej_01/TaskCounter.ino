void TaskCounter(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  //-----------para hacer que una tarea sea periodica ----------------------------------------
    TickType_t xPreviousWakeTime;
    xPreviousWakeTime=xTaskGetTickCount(); //Ultima vez que la tarea paso del estado Blocked al estado Ready 
                                           //se hace igual al numero de ticks actuales
  //------------------------------------------------------------------------------------------    
  
  /*
    TaskCounter: 
  */
    bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;        //activar la FSM
    }else{     
        if(Update == ON)                //Update se hace ON cada 1/2 segundo
        {
          CounterUpdate();                 //actualiza TimeDisp[]
          tm1637.display(CounterDisp);     //lo muestra en display de 7 segs
          Update = OFF;
        }                                        
   }  
   vTaskDelayUntil(&xPreviousWakeTime,100/ portTICK_PERIOD_MS );                                                                
  }//end for
  
}//end task
//===========================================================

