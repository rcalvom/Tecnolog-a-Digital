//===================================================
//================== TaskReceive =======================

void TaskReceive(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
  /*
    TaskReceive: Recibe informacion desde el PC:dr,dd,dl,du
  */

    enum state_type{Receive};
    state_type state; 
    int8_t info[4];

    portBASE_TYPE xStatus;    //estado de la cola de mensajes
    bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;        //activar la FSM
      state=Receive;              //ir al estado Start  
    }else{
      switch(state){    
        case Receive:   
          if(Serial.available()>3){
            info[0] = Serial.read()-48;    
            info[1] = Serial.read()-48;    
            info[2] = Serial.read()-48;    
            info[3] = Serial.read()-48;
            Update = ON;
            xQueueSendToBack(xQueue,&info,0); 
          }          
          break; 
      }//end switch         
    }//end if
    vTaskDelay(35/portTICK_PERIOD_MS ); //esperar 100ms en el estado bloqueado                                                                     
  }//end for
}//end task
//===========================================================
