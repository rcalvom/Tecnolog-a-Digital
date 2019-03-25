//===================================================
//================== TaskBlinkControl =======================

void TaskBlinkControl(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  //-----------para hacer que una tarea sea periodica ----------------------------------------
    TickType_t xPreviousWakeTime;
    xPreviousWakeTime=xTaskGetTickCount(); //Ultima vez que la tarea paso del estado Blocked al estado Ready 
                                           //se hace igual al numero de ticks actuales
  //------------------------------------------------------------------------------------------  
  
  /*
    TaskBlinkControl: cambia la frecuencia de encendido del led dependiendo del valor de entrada analoga en A0;
  */  
    
  enum state_type{s0,s1};  //agregar estados de ser necesario
  state_type state;
  bool Fsm_isActive=false;

  int sensorValue;     //variable to store the value coming from the sensor
  int val;             //sensorValue en el rango 0-40 
  int count;           //variable contadora de tiempo

  for (;;) // A Task shall never return or exit.
  {     
    if (Fsm_isActive==false){
      Fsm_isActive=true;  //activar la FSM
      state=s0;
    }else{
      //read the value from the sensor:
      sensorValue = analogRead(sensorPin);  //0<sensorValue<1023 (10 bits A/D converter)
      //map sensorValue to  1-40 range
      val= map(sensorValue, 0, 1023, 1, 40);
      Serial.println(val);
      //led blink control:     
      switch(state){       
        //ToDo:
        case s0:  
          // turn the ledPin on
          digitalWrite(ledPin,HIGH);
          if(++count>=val){         //delay=val*50ms
            count=0;
            state=s1;            
          }
          break;               
        case s1:
          // turn the ledPin off
          digitalWrite(ledPin,LOW);
          if(++count>=val){         //delay=val*50ms
            count=0;
            state=s0;            
          }      
          break;
      }//end switch
    }//end if
    vTaskDelayUntil(&xPreviousWakeTime,50/ portTICK_PERIOD_MS ); //tarea periodica: periodo 50 ms                                                                                                           
  }//end for
}//end task
//===========================================================


