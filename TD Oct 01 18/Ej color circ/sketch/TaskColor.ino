//===================================================
//================== TaskColors =======================

void TaskColors(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  /*
    TaskColor: recibe en mensaje data: data[0]:direccion:1 derecha,2 izquierda; data[1]:pos en x(pixeles); 
               y transmite color del circulo serialmente
  */
  byte data[2];            //data recibida en mensaje
  portBASE_TYPE xStatus;   //estado de la cola de mensajes
  
  enum state_type{DoColor};
  state_type state;
  bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=DoColor;
    }else{ 
      switch(state){
        case DoColor:      
          do{
            xStatus=xQueueReceive(xQueue,data,0);   //recibir el mensaje al principio de la cola, si no esta vacia          
          }while (xStatus != pdPASS);               //mientras la cola no tenga mensaje: repetir
          //manejo de color:   
          if (((data[0]==1) && ((data[1]<=200/3)||(data[1]>=400/3)))||((data[0]==0)&&((data[1]>=200/3)&&(data[1]<=400/3)))){
            Serial.write('G');  
          }else {      
            Serial.write('R'); 
          }
          //permanecer en este estado:            
          state=DoColor;
          break;
      }//end switch
    }//end if
    vTaskDelay(50 / portTICK_PERIOD_MS );  //esperar 200 ms en el estado bloqueado                                                                                                                
  }//end for
}//end task
//===========================================================


