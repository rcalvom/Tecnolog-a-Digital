//================== TaskLeds1 =======================

void TaskLeds1(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
  /*
    TaskLeds1: Manejo de leds Rojo y Verde
  */

    enum state_type{Red,Green,Yellow};
    state_type state; 
    bool Fsm_isActive=false;
    unsigned long timeCounter=0,r;
    String stringToSend;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;      //activar la FSM
      state=Red;              //ir al estado Red
      stringToSend="Red_m";
      timeCounter=0;          //inicializar el contador de tiempo 
      xQueueSendToBack(xQueue,&stringToSend,0); //colocar mensaje al final de la cola            
      outSerial("Red");       //al entrar (en) al estado Red llamar la funcion outSerial, en:outSerial("Red");
      RedON(HIGH);
      YellowON(LOW);
      GreenON(LOW);
    }else{
      switch(state){
        case Red:             
          timeCounter++;         //Incrementar contador de Tiempo 
          if(timeCounter>=2){    //Si han pasado 2 o mas segundos:  
            r=random(0,2);
            if(r==0){                                            
              state=Green;           //ir al estado Green
              stringToSend="Green_m";//mensaje a enviar
              xQueueSendToBack(xQueue,&stringToSend,0); //colocar mensaje al final de la cola 
              timeCounter=0;       //hacer un reset del contador de tiempo        
              outSerial("Green");
              RedON(LOW);
              YellowON(LOW);
              GreenON(HIGH);
            }else{     
              state=Yellow;           //ir al estado Yellow
              stringToSend="Yellow_m";//mensaje a enviar
              xQueueSendToBack(xQueue,&stringToSend,0); //colocar mensaje al final de la cola  
              timeCounter=0;       //hacer un reset del contador de tiempo        
              outSerial("Yellow");
              RedON(LOW);
              YellowON(HIGH);
              GreenON(LOW);
            }            
          }
          break;
        case Green:
          timeCounter++;                //Incrementar contador de Tiempo 
          if(timeCounter>=5){           //Si han pasado 5 o mas segundos:         
            state=Red;                  //ir al estado Red
            stringToSend="Red_m";       //mensaje a enviar
            xQueueSendToBack(xQueue,&stringToSend,0); //colocar mensaje al final de la cola                    
            timeCounter=0;              //hacer un reset del contador de tiempo
            outSerial("Red");           //al entrar (en) al estado Red llamar la funcion outSerial, en:outSerial("Red");          
            RedON(HIGH);
            YellowON(LOW);
            GreenON(LOW);
          }
          break;
        case Yellow:
          timeCounter++;                //Incrementar contador de Tiempo 
          if(timeCounter>=5){           //Si han pasado 2 o mas segundos:              
            state=Red;                  //ir al estado Red
            stringToSend="Red_m";       //mensaje a enviar
            xQueueSendToBack(xQueue,&stringToSend,0); //colocar mensaje al final de la cola               
            timeCounter=0;              //hacer un reset del contador de tiempo
            outSerial("Red");           //al entrar (en) al estado Red llamar la funcion outSerial, en:outSerial("Red"); 
            RedON(HIGH);
            YellowON(LOW);
            GreenON(LOW);
          }
          break;    
      }//end switch         
    }//end if
    vTaskDelay(1000 / portTICK_PERIOD_MS ); // //esperar 1 segundo en el estado bloqueado                                                                     
  }//end for
}//end task

//===================================================
