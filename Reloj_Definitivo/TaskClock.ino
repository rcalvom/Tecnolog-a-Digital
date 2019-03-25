void TaskClock(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  //-----------para hacer que una tarea sea periodica ----------------------------------------
    TickType_t xPreviousWakeTime;
    xPreviousWakeTime=xTaskGetTickCount(); //Ultima vez que la tarea paso del estado Blocked al estado Ready 
                                           //se hace igual al numero de ticks actuales
  //------------------------------------------------------------------------------------------    
  
  /*
    TaskClock: 
  */
    bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;        //activar la FSM
    }else{     
      BtnTime.read();
      BtnAlarm.read(); 
      BtnMin.read();  
      BtnHour.read();
      BtnLed.read(); 

      if(BtnAlarm.isPressed()==false){  //si boton alarma no esta oprimido mostrar hora actual
        if(Update == ON)                //Update se hace ON cada 1/2 segundo
        {
          TimeUpdate();                 //actualiza TimeDisp[]
          tm1637.display(TimeDisp);     //lo muestra en display de 7 segs
        } 
      }
      else{                            //si boton alarma esta oprimido mostrar hora de la alarma
        AlarmUpdate();                 //actualiza AlarmDisp[]
        tm1637.display(AlarmDisp);     //lo muestra en display de 7 segs
      }                                          
   }  
    vTaskDelayUntil(&xPreviousWakeTime,100/ portTICK_PERIOD_MS ); 
    //vTaskDelay(100 / portTICK_PERIOD_MS ); //esperar 100ms en el estado bloqueado                                                                        
  }//end for
  
}//end task
//===========================================================

