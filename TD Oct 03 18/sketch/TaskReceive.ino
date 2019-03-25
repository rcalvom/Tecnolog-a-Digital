//===================================================
//================== TaskReceive =======================

void TaskReceive(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
  /*
    TaskReceive: Recibe informacion desde el PC:rectSupY, circPosX, circPosY.
  */

    enum state_type{Start,Receive};
    state_type state; 
    byte info[3]; //rectSupY:info[0],circPosX:info[1],circPosY:info[2]; enviada serialmente desde PC 

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
          if(Serial.available()>2){
            info[0]=Serial.read();
            info[1]=Serial.read();
            info[2]=Serial.read();
            xQueueSendToBack(xQueue,info,0); //se envia mensaje a TaskPosXY;
          }          
          break; 
      }//end switch         
    }//end if
    vTaskDelay(100 / portTICK_PERIOD_MS ); //esperar 100ms en el estado bloqueado                                                                     
  }//end for
}//end task
//===========================================================
