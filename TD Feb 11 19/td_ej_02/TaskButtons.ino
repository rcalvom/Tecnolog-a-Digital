void TaskButtons(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  //-----------para hacer que una tarea sea periodica ----------------------------------------
    TickType_t xPreviousWakeTime;
    xPreviousWakeTime=xTaskGetTickCount(); //Ultima vez que la tarea paso del estado Blocked al estado Ready 
                                           //se hace igual al numero de ticks actuales
  //------------------------------------------------------------------------------------------    
  
  /*
    TaskButtons: 
  */
    bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;        //activar la FSM
    }else{     
      BtnReset.read();
      if (BtnReset.wasPressed()) flagReset=true;                                       
      BtnSet.read();
      if(BtnSet.wasPressed()) flagSet = true;
      BtnPulsacion.read();
      if(BtnPulsacion.wasPressed()) pulsaciones = true;

      AnalogRead = analogRead(A0);
      AnalogMap = map(AnalogRead,0,1023,0,200);
      Serial.println(AnalogMap);
      if(AnalogMap>=100){
        flagReset = true;
      }
      
   }  
    vTaskDelayUntil(&xPreviousWakeTime,100/ portTICK_PERIOD_MS );                                                                      
  }//end for
  
}//end task
//===========================================================

