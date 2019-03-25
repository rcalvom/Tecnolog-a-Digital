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
  int sensorValue;
  float val;
  int count;
  int8_t arreglo[4]; 


  enum state_type{s0,s1};
   state_type state;

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      count=0;
    }else{
      switch(state){
        case s0:
          sensorValue = analogRead(sensorPin);
          val = map(sensorValue, 0, 1023, 0, 30);
          arreglo[count] = val;
          count++;
          if(count>=4){
            state=s1;          
            count=0; 
          }
        break;
        case s1:
          tm1637.display(arreglo);
          tm1637.point(POINT_ON);
          state=s0;
        break;
      }
      
    }//end if
    vTaskDelayUntil(&xPreviousWakeTime,20/portTICK_PERIOD_MS ); //tarea periodica: periodo 200 ms                                                                                                        
  }//end for
}//end task
//===========================================================


