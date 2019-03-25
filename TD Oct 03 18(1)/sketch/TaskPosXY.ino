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
    
  enum state_type{recibirMensaje,movVertical,movHorizontal};
  state_type state;
  bool Fsm_isActive=false;
  int ref; 

  int circPosX,circPosY,rectSupY;

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
            
            rectSupY = info[0];
            circPosX = info[1];
            circPosY = info[2];
            ref=rectSupY+20;          
            state = movVertical;
          break;         
        case movVertical: 
          if(ref<=circPosY){
            circPosY-=2;
          }else{
            circPosY+=2;
          }
          info1[0]=circPosX;
          info1[1]=circPosY;
          xQueueSendToBack(xQueue1,&info1,0);
          if(circPosY==ref||circPosY+1==ref||circPosY-1==ref){
            state=movHorizontal;
          }
          break;
        case movHorizontal:
          info1[0]+=2;
          xQueueSendToBack(xQueue1,&info1,0); 
          if(info1[0]>=189){
            state=recibirMensaje;
          }
          break;
      }//end switch
    }//end if
    vTaskDelay(100 / portTICK_PERIOD_MS );  //esperar 100 ms en el estado bloqueado                                                                                                                
  }//end for
}//end task
//===========================================================


