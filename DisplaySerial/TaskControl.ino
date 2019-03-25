//===================================================
//================== TaskControl =======================

void TaskControl(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  int8_t info1[4];
  portBASE_TYPE xStatus;  //estado de la cola de mensajes
    
  enum state_type{s0};  //agregar mas estados de ser necesario
  state_type state;
  bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=s0;
    }else{
      //recibir mensaje enviado por TaskReceive 
      do{
        xStatus=xQueueReceive(xQueue,&info1,0);     //recibir el mensaje al principio de la cola, si no esta vacia          
      }while (xStatus != pdPASS);                 //mientras la cola no tenga mensaje: repetir        
   
      switch(state){       
        case s0:
          if(Update = ON){
            Update = OFF;
            tm1637.display(info1);
            
          }
        break;         
      }//end switch
    }//end if
    vTaskDelay(35 / portTICK_PERIOD_MS );  //esperar 100 ms en el estado bloqueado                                                                                                                
  }//end for
}//end task
//===========================================================


