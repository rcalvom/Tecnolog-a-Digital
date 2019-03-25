//===================================================
//================== TaskPosXY =======================

void TaskPosXY(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  /*
    TaskPosXY: calcula la posicion en (x,y) que debe tener el circulo en su desplazamiento
  */

  byte posCirc[2]; //posicion en x:posCirc[0] y en y:posCirc[1] del circulo que será calculada y comunicada a TaskTransmit en mensaje 
    
  enum state_type{start,right,diag,right2,teleport};
  state_type state;
  bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=start;
    }else{ 
      switch(state){
        case start: 
          xSemaphoreTake(xBinSem_E,portMAX_DELAY);  //se toma el semáforo
          posCirc[0]=20;                            //posicion inicial del circulo en eje x
          posCirc[1]=20;                           //posicion inicial del circulo en eje y
          xQueueSendToBack(xQueue,posCirc,0);       //enviar mensaje con posicion en (x,y)
          state=right;                              //ir a desplazamiento a la derecha          
          break;         
        case right: 
          posCirc[0]+=2;
          xQueueSendToBack(xQueue,&posCirc,0); 
          if (posCirc[0]>=179)state=diag;
          break;
        case diag: 
          posCirc[0]-=2;
          posCirc[1]+=2;
          xQueueSendToBack(xQueue,&posCirc,0); 
          if (posCirc[0]<=20)state=right2;
          break;
         case right2: 
          posCirc[0]+=2;          
          xQueueSendToBack(xQueue,&posCirc,0); 
          if (posCirc[0]>=179)state=teleport;
          break;
        case teleport: 
          posCirc[0]=20;                            //posicion inicial del circulo en eje x
          posCirc[1]=20;                           //posicion inicial del circulo en eje y
          xQueueSendToBack(xQueue,posCirc,0);       //enviar mensaje con posicion en (x,y)
          state=right;                              //ir a desplazamiento a la derecha          
          break;       
      }//end switch
    }//end if
    vTaskDelay(100 / portTICK_PERIOD_MS );  //esperar 100 ms en el estado bloqueado                                                                                                                
  }//end for
}//end task
//===========================================================


