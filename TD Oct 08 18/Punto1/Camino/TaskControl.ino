//===================================================
//================== TaskControl =======================

void TaskControl(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  /*
    TaskControl: calcula la posicion en (x,y) que debe tener el circulo en su desplazamiento
  */

  byte info[4];           //dr:info[0],dd:info[1],dl:info[2],du:info[3];
                          //comunicada desde TaskReceive mediante mensaje 
  byte info1[1];          //'R':right;'L':left;'U':up;'D':down;'S':stop; comunicada a TaskTransmit mediante mensaje 
  portBASE_TYPE xStatus;  //estado de la cola de mensajes
    
  enum state_type{s0,s1,s2,s3,s4,s5,s6,s7,s8};  //agregar mas estados de ser necesario
  state_type state;
  bool Fsm_isActive=false;

  int dr,dd,dl,du; //dr:distance_right;dd:distance_down;dr:distance_left;dr:distance_up;

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=s0;
    }else{
      //recibir mensaje enviado por TaskReceive 
      do{
        xStatus=xQueueReceive(xQueue,info,0);     //recibir el mensaje al principio de la cola, si no esta vacia          
      }while (xStatus != pdPASS);                 //mientras la cola no tenga mensaje: repetir        
      dr=info[0];
      dd=info[1];
      dl=info[2];
      du=info[3]; 

      //control del movil:     
      switch(state){       
        case s0:
          info1[0] = 'R';
          xQueueSendToBack(xQueue1,&info1,0);
          if(info[0]<=20){
            state=s1;
          }
        break;
        case s1:
          info1[0] = 'D';
          xQueueSendToBack(xQueue1,&info1,0);
          if(info[1]<=20){
            state=s2;
          }
        break;
        case s2:
          info1[0] = 'R';
          xQueueSendToBack(xQueue1,&info1,0);
          if(info[0]<=20){
            state=s3;
          }
        break;
        case s3:
          info1[0] = 'U';
          xQueueSendToBack(xQueue1,&info1,0);
          if(info[3]<=20){
            state=s4;
          }
        break;
        case s4:
          info1[0] = 'R';
          xQueueSendToBack(xQueue1,&info1,0);
          if(info[0]<=20){
            state=s5;
          }
        break;
        case s5:
          info1[0] = 'D';
          xQueueSendToBack(xQueue1,&info1,0);
          if(info[1]<=20){
            state=s6;
          }
        break;
        case s6:
          info1[0] = 'L';
          xQueueSendToBack(xQueue1,&info1,0);
          if(info[2]<=20){
            state=s7;
          }
        break;
        case s7:
          info1[0] = 'D';
          xQueueSendToBack(xQueue1,&info1,0);
          if(info[1]<=20){
            state=s8;
          }
        break;
        case s8:
          info1[0] = 'S';
          xQueueSendToBack(xQueue1,&info1,0);
        break;
         
      }//end switch
    }//end if
    vTaskDelay(35 / portTICK_PERIOD_MS );  //esperar 100 ms en el estado bloqueado                                                                                                                
  }//end for
}//end task
//===========================================================


