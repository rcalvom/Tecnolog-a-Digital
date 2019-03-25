//===================================================
//================== TaskTransmit =======================

void TaskTransmit(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
  /*
    Tasktransmit: Transmite serialmente posicion en (x,y) del circulo
  */

    enum state_type{Start,Transmit};
    state_type state; 
    byte posCirc[2];          //posicion en x:posCirc[0] y en y:posCirc[1] del circulo recibidas desde TaskPosXY

    portBASE_TYPE xStatus;    //estado de la cola de mensajes
    bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;        //activar la FSM
      state=Start;              //ir al estado Start  
    }else{
      switch(state){
        case Start:
          Serial.write('Q');              //proceso de sincroniuzacion 
          delay(500);                
          if (Serial.available()>0){
            if(Serial.read()=='A'){       //si ya estan sincronizados
              xSemaphoreGive(xBinSem_E);  //se da el semaforo
              state=Transmit;      
            }
          }
          break;
        case Transmit:   
          do{
            xStatus=xQueueReceive(xQueue,posCirc,0);   //recibir el mensaje al principio de la cola, si no esta vacia          
          }while (xStatus != pdPASS);                  //mientras la cola no tenga mensaje: repetir
          Serial.write(posCirc[0]);                    //transmitir serilmente posicion en x
          Serial.write(posCirc[1]);                    //transmitir serilmente posicion en y 
          break; 
      }//end switch         
    }//end if
    vTaskDelay(100 / portTICK_PERIOD_MS ); //esperar 100ms en el estado bloqueado                                                                     
  }//end for
}//end task
//===========================================================
