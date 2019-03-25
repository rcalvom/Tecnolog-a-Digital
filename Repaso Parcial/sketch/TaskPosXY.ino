//===================================================
//================== TaskPosXY =======================

void TaskPosXY(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  /*
    TaskPosXY: calcula la posicion en (x,y) que debe tener el circulo en su desplazamiento
  */

  byte info[3];           //rectSupY:info[0],circPosX:info[1],circPosY:info[2]; comunicada desde TaskReceive mediante mensaje 
  byte info1[2];          //circPosX:info1[0],circPosY:info1[1]; comunicada a TaskTransmit mediante mensaje 
  portBASE_TYPE xStatus;  //estado de la cola de mensajes
    
  enum state_type{setupVariables,movVerticalMeter,movHorizontalMeter};
  state_type state;
  bool Fsm_isActive=false;
  int tunel; 

  int circPosX,circPosY,rectSupY;

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=setupVariables;
    }else{ 
      switch(state){
        case setupVariables:
          do{
            xStatus=xQueueReceive(xQueue,&info,0);
          }while (xStatus != pdPASS);
          rectSupY = info[0];
          info1[0] = info[1];
          info1[1] = info[2];
          tunel = rectSupY + 15;
          state = movVerticalMeter;
        break;
        case movVerticalMeter:
          if(info1[1] < tunel){
            info1[1]+=2;
          }
          if(info1[1] > tunel){
            info1[1]-=2;
          }
          if((info1[1] >= tunel-1)&&(info1[1] <= tunel+1)){
            state = movHorizontalMeter;
          }
          xQueueSendToBack(xQueue,&info1,0);
        break;
        case movHorizontalMeter:
        info1[0]+=2;
          xQueueSendToBack(xQueue,&info1,0);
        break;
      }//end switch
    }//end if
    vTaskDelay(100 / portTICK_PERIOD_MS );  //esperar 100 ms en el estado bloqueado                                                                                                                
  }//end for
}//end task
//===========================================================
