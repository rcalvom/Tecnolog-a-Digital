//===================================================
//================== TaskReceive =======================

void TaskReceive(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
  /*
    TaskReceive: Recepcion de data por puerto serial:data[0]:direccion:1 derecha,2 izquierda; data[1]:pos en x(pixeles);
  */

    enum state_type{Receive};
    state_type state; 
    byte data[2]; //data recibida por puerto serial y enviado luego en mensaje a TaskColor
    bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;       //activar la FSM
      state=Receive;           //ir al estado Receive  
    }else{
      switch(state){
        case Receive:             
          // check if data has been sent from the computer:
          if (Serial.available()>1) {                //verifica si han llegado 2 bytes
            Serial.readBytes(data,2);                //se guardan en el arreglo data 
            xQueueSendToBack(xQueue,data,0);         //data enviado a TaskColor
          }
          state=Receive;
          break; 
      }//end switch         
    }//end if
    vTaskDelay(50 / portTICK_PERIOD_MS ); //esperar 200ms en el estado bloqueado                                                                     
  }//end for
}//end task
//===========================================================
