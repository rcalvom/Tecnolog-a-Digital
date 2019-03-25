//===================================================
//================== TaskLamp =======================

void TaskLamp(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  //-----------para hacer que una tarea sea periodica ----------------------------------------
    TickType_t xPreviousWakeTime;
    xPreviousWakeTime=xTaskGetTickCount(); //Ultima vez que la tarea paso del estado Blocked al estado Ready 
                                           //se hace igual al numero de ticks actuales
  //------------------------------------------------------------------------------------------

  /*
    TaskLamp:
  */
    bool Fsm_isActive=false;
    enum state_t {APAGADO,MEDIA,ALTA,DELAY};
    static state_t state=APAGADO;
    int contador=0;      //contador de tiempo
    int nc=0;            //numero de cambios experimentados por el sensor
    bool ss=false;       //sensor state: true si ha cambiado
 
  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=APAGADO;            //ir al estado START
    }else{ 
      ss=readSensor();    //determinar si hay cambio en el sensor
      switch(state){
      case APAGADO:      
        analogWrite(ledPin,0); //luz apagada
        if(ss) {               //si hay cambio en el sensor 
            state=MEDIA;       //ir a luz media    
        }
        break;
      case MEDIA: 
      analogWrite(ledPin,80);  //luz media
      if(ss) {                 //si hay cambio en el sensor
          nc++;                //incrementar numero de cambios
          state=DELAY;         //ir a retardo de tiempo      
      };
      break; 
    case DELAY:                //delay de 100+10*100=1100 ms
      contador++;
      if(ss)nc++; 
      if (contador==10){
        contador=0;
        if(nc>=2) state=APAGADO; //si ha habido dos o mas  cambios en 1100ms apagar luz
        else state=ALTA;         //sino pasar a luz alta
        nc=0;           
      }
      break;      
    case ALTA: 
      analogWrite(ledPin,255); //luz alta
      if(ss) {            //si hay cambio en sensor
          state=APAGADO;  //apagar luz        
      };
      break;                
    }//end switch     
   }//end else       
    vTaskDelayUntil(&xPreviousWakeTime,100/ portTICK_PERIOD_MS ); // Bloquea task de forma periodica por 100 ms                                                                             //esperar 1 segundo en el estado bloqueado                                                                                                                
  }//end for
}//end task
//===========================================================

