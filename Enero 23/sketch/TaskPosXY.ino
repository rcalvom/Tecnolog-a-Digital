//===================================================
//================== TaskPosXY =======================

void TaskPosXY(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  /*
    TaskPosXY: calcula la posicion en (x,y) que debe tener el circulo en su desplazamiento
  */

  byte info[3];           //rectSupY:info[0],circPosX:info[1],circPosX:info[2]; comunicada desde TaskReceive mediante mensaje 
  byte info1[2];          //circPosX:info1[0],circPosY:info1[1]; comunicada a TaskTransmit mediante mensaje 
  portBASE_TYPE xStatus;  //estado de la cola de mensajes
    
  enum state_type{recibirMensaje,movVertical,movHorizontal,movVertical2,movHorizontal2,Stop};
  state_type state;
  bool Fsm_isActive=false;
  int ref; 

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=recibirMensaje;
    }else{ 
      switch(state){
        case recibirMensaje:           
            do{
              xStatus=xQueueReceive(xQueue,&info,0);
            }while (xStatus != pdPASS);     
            info1[0]=info[1];
            info1[1]=info[2];
            state=movVertical;
            break;         
        case movVertical: 
          if(info[0]+20>=100){
            if(info1[1]<=info[0]-15){
              info1[1]+=2;
            }else{
              info1[1]-=2;
            }
            if(abs(info1[1]-(info[0]-15))<=1){
              state=movHorizontal;
            }
          }else{
            if(info1[1]<=info[0]+55){
              info1[1]+=2;
            }else{
              info1[1]-=2;
            }
            if(abs(info1[1]-(info[0]+55))<=1){
              state=movHorizontal;
            }
          }
          xQueueSendToBack(xQueue1,&info1,0);
          break;
        case movHorizontal:
          info1[0]+=2;
          if(info1[0]>=189){
            state=movVertical2;
          }
          xQueueSendToBack(xQueue1,&info1,0); 
          break;
        case movVertical2:
          if(info[0]+20>=info1[1]){
            info1[1]+=2;
          }else{
            info1[1]-=2;
          }
          if(abs(info1[1]-(info[0]+20))<=1){
            state=movHorizontal2;
          }
          xQueueSendToBack(xQueue1,&info1,0); 
          break;
        case movHorizontal2:
          info1[0]-=2;
          if(info1[0]<=11){
            state=Stop;
          }
          xQueueSendToBack(xQueue1,&info1,0); 
          break;
        case Stop:
          //caso final
          break;
      }//end switch
    }//end if
    vTaskDelay(100 / portTICK_PERIOD_MS );  //esperar 100 ms en el estado bloqueado                                                                                                                
  }//end for
}//end task
//===========================================================


