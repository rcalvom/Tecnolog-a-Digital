//===================================================
//================== TaskReceive =======================
void TaskReceive(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
  /*
    TaskReceive: Recibe informacion desde el PC: velocidad y posicion en x del objetivo
  */

    enum state_type{Start,Receive};
    state_type state; 
    byte info[2]; //velocidad del objetivo:info[0],posicion x del objetivo:info[1];

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
              state=Receive;      
            }
          }
          break;      
        case Receive:   
          if(Serial.available()>1){
            info[0]=Serial.read();           //velocidad del objetivo
            info[1]=Serial.read();           //posicion en x del objetivo
            xQueueSendToBack(xQueue,info,0); //se envia mensaje a TaskPosXY;
          }          
          break; 
      }//end switch         
    }//end if
    vTaskDelay(35 / portTICK_PERIOD_MS ); //esperar 100ms en el estado bloqueado                                                                     
  }//end for
}//end task
//===========================================================
