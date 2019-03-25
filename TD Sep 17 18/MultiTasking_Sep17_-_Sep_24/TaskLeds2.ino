void TaskLeds2(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  /*
    TaskLeds2: Manejo de leds Azul y Amarillo
  */
  String stringReceived;  //mensaje recibido
  portBASE_TYPE xStatus;  //estado de la cola de mensajes
  
  enum state_type{Blue};
  state_type state;
  bool Fsm_isActive=false;

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=Blue;
      outSerial("Blue");
      BlueON(HIGH);
    }else{ 
      switch(state){
        case Blue:
        
          do{
            xStatus=xQueueReceive(xQueue,&stringReceived,0);   //recibir el mensaje al principio de la cola, si no esta vacia          
          }while (xStatus != pdPASS);                          //mientras la cola no tenga mensaje repetir
          
          if(stringReceived.equals("Red_m")){
            Serial.println("RED_LED");                         
          }else if (stringReceived.equals("Green_m")) {
            Serial.println("Green_LED");  
          }else{
            Serial.println("Yellow_LED");   
          }
          state=Blue;
          break;
      }//end switch
    }//end if
    vTaskDelay(100 / portTICK_PERIOD_MS );         //esperar 1 segundo en el estado bloqueado                                                                                                                
  }//end for
}//end task
//===========================================================
