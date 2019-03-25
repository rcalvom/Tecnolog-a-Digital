//===================================================
//================== TaskTransmit =======================

void TaskTransmit(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
  /*
    TaskTransmit: envia informacion al PC:circPosX, circPosY.
  */

    enum state_type{Transmit};
    state_type state; 
    byte info1[2]; //circPosX:data[0],circPosY:data[1]; enviada serialmente al PC 

    portBASE_TYPE xStatus;    //estado de la cola de mensajes
    bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;        //activar la FSM
      state=Transmit;              //ir al estado Start  
    }else{
      switch(state){    
        case Transmit:   
          do{
            xStatus=xQueueReceive(xQueue1,info1,0);     //recibir el mensaje al principio de la cola, si no esta vacia          
          }while (xStatus != pdPASS);                   //mientras la cola no tenga mensaje: repetir 
          Serial.write(info1[0]);                       //transmitir al PC circPosX
          Serial.write(info1[1]);                       //transmitir al PC circPosY
          break; 
      }//end switch         
    }//end if
    vTaskDelay(100 / portTICK_PERIOD_MS ); //esperar 100ms en el estado bloqueado                                                                     
  }//end for
}//end task
//===========================================================
