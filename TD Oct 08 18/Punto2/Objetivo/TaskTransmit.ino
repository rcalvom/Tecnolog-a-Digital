//===================================================
//================== TaskTransmit =======================

void TaskTransmit(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
  /*
    TaskTransmit: envia comando para lanzar el interceptor
  */

    enum state_type{Transmit};
    state_type state; 
    byte info1[1]; //info1[0]:'F':Fire:comando para lanzar el interceptor 

    portBASE_TYPE xStatus;    //estado de la cola de mensajes
    bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;           //activar la FSM
      state=Transmit;              //ir al estado Start  
    }else{
      switch(state){    
        case Transmit:   
          do{
            xStatus=xQueueReceive(xQueue1,info1,0);     //recibir el mensaje al principio de la cola, si no esta vacia          
          }while (xStatus != pdPASS);                   //mientras la cola no tenga mensaje: repetir 
          Serial.write(info1[0]);                       //transmitir al PC comando
          break; 
      }//end switch         
    }//end if
    vTaskDelay(35 / portTICK_PERIOD_MS ); //esperar 100ms en el estado bloqueado                                                                     
  }//end for
}//end task
//===========================================================
