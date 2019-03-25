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
  int count;           //variable contadora
  int prom;
  int sensorValue;
  float val;


  enum state_type{s0,s1};
   state_type state;

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      count=0;
      prom=0;
    }else{
      switch(state){
        case s0:
         sensorValue = analogRead(sensorPin);
         val = map(sensorValue, 0, 1023, 0, 500);
         prom+=val;
         count++;
         if(count==4){
          state=s1;          
          count=0;
         }
        break;
        case s1:
          prom/=5;
          tm1637.displayNum(val);
          tm1637.point(POINT_ON);
          Serial.println(val);
          state=s0;
          prom=0;
        break;
      }
      
    }//end if
    vTaskDelayUntil(&xPreviousWakeTime,20/portTICK_PERIOD_MS ); //tarea periodica: periodo 200 ms                                                                                                        
  }//end for
}//end task
//===========================================================


