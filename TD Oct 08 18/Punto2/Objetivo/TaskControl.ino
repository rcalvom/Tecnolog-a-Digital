//===================================================
//================== Control =======================

void TaskControl(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  /*
    TaskControl: comanda el lanzamiento dl interceptor para impactar el objetivo
  */

  byte info[2];           //velocidad del objetivo:info[0],posicion del objetivo:info[1];
                          //comunicada desde TaskReceive mediante mensaje 
  byte info1[1];          //'F':Fire:comando para lanzar el interceptor
  portBASE_TYPE xStatus;  //estado de la cola de mensajes
    
  enum state_type{s0,s1,s2}; //agregar mas estados de ser necesario
  state_type state;
  bool Fsm_isActive=false;

//
  float vel;       //velocidad del objetivo
  int posx;        //posicion en x del objetivo
  int cont=0;

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=s0;
    }else{ 
      //recibir mensaje desde TaskReceive
      do{
        xStatus=xQueueReceive(xQueue,info,0);     //recibir el mensaje al principio de la cola, si no esta vacia          
      }while (xStatus != pdPASS);                 //mientras la cola no tenga mensaje: repetir 

      //ecuaciones para detrminar vel y posx a partir de la informacion en el mensaje: 
      //ToDo:     
        vel = ((2/255)*float(info[0]))+1;
        posx = (400L*info[1])/255;
      //estados: calculos requeridos y envio de comando 'F' para lograr impacto
      //ToDo:
      switch(state){
        case s0:
            if(abs((posx/vel)-(cont+100))<=4){
              info1[0]= 'F';
              xQueueSendToBack(xQueue1,&info1,0);
            }
          cont++;
        break;
      }//end switch  
    }//end if
    vTaskDelay(35 / portTICK_PERIOD_MS );  //esperar 100 ms en el estado bloqueado                                                                                                                
  }//end for
}//end task
//===========================================================


