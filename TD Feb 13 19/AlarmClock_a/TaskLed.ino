void TaskLed (void *pvParameters){
  (void) pvParameters;
  
  TickType_t xPreviousWakeTime;
  xPreviousWakeTime=xTaskGetTickCount();

  enum state_type{RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE, RANDOM1 ,RANDOM2, Off};
  state_type state;
  state_type state1;
  bool Fsm_isActive=false;
  int count = 0;
  int count1 = 0;
  int countbtn = 0;
  int rgb[3];
  
  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;        //activar la FSM
      state = RANDOM1;
      state1 = RANDOM1;
    }else{  
      if(BtnLed.isPressed()){
          count++;
          countbtn++;
      }else{
        count = 0;
      }
      if(BtnLed.isReleased()){
        if(countbtn < 10 && countbtn !=0){
          if(state == state1){
            state = Off;
          }else{
            state = state1;
          }
        }
        countbtn=0;
      }
      if(BtnLed.wasPressed()){
        count1 = 0;
      }
       switch(state){
          case RED:
            digitalWrite(Red,HIGH);
            digitalWrite(Green,LOW);
            digitalWrite(Blue,LOW);
            if(count > 9){
              count = 0;
              state = GREEN;
              state1 = GREEN;
            }
          break;                         
          case GREEN:
            digitalWrite(Red,LOW);
            digitalWrite(Green,HIGH);
            digitalWrite(Blue,LOW);
            if(count > 9){
              count = 0;
              state = BLUE;
              state1 = BLUE;
            }
          break;
          case BLUE:
            digitalWrite(Red,LOW);
            digitalWrite(Green,LOW);
            digitalWrite(Blue,HIGH);
            if(count > 9){
              count = 0;
              state = YELLOW;
              state1 = YELLOW;
            }
          break;
          case YELLOW:
            digitalWrite(Red,HIGH);
            digitalWrite(Green,HIGH);
            digitalWrite(Blue,LOW);
            if(count > 9){
              count = 0;
              state = MAGENTA;
              state1 = MAGENTA;
            }
          break;
          case MAGENTA:
            digitalWrite(Red,HIGH);
            digitalWrite(Green,LOW);
            digitalWrite(Blue,HIGH);
            if(count > 9){
              count = 0;
              state = CYAN;
              state1 = CYAN;
            }
          break;
          case CYAN:
            digitalWrite(Red,LOW);
            digitalWrite(Green,HIGH);
            digitalWrite(Blue,HIGH);
            if(count > 9){
              count = 0;
              state = WHITE;
              state1 = WHITE;
            }
          break;
          case WHITE:
            digitalWrite(Red,HIGH);
            digitalWrite(Green,HIGH);
            digitalWrite(Blue,HIGH);
            if(count > 9){
              count = 0;
              state = RANDOM1;
              state1 = RANDOM1;
            }
          break;
          case RANDOM1:
            do{
              rgb[0] = random(0,2);
              rgb[1] = random(0,2);
              rgb[2] = random(0,2);
            }while((rgb[0]+rgb[1]+rgb[2]) == 0);
            if(count1 == 0){
              digitalWrite(Red,rgb[0]);
              digitalWrite(Green,rgb[1]);
              digitalWrite(Blue,rgb[2]);
            }

            if(count1 < 3){
              count1++;
            }else{
              count1=0;
            }
            if(count > 9){
              count = 0;
              count1 = 0;
              state = RANDOM2;
              state1 = RANDOM2;
            }
          break;
          case RANDOM2:
            do{
              rgb[0] = random(0,2);
              rgb[1] = random(0,2);
              rgb[2] = random(0,2);
            }while((rgb[0]+rgb[1]+rgb[2]) == 0);
            if(count1 == 0){
              digitalWrite(Red,rgb[0]);
              digitalWrite(Green,rgb[1]);
              digitalWrite(Blue,rgb[2]);
            }

            if(count1 < 14){
              count1++;
            }else{
              count1=0;
            }
            if(count > 9){
              count = 0;
              count1 = 0;
              state = RED;
              state1 = RED;
            }
          break;
          case Off:
            digitalWrite(Red,LOW);
            digitalWrite(Green,LOW);
            digitalWrite(Blue,LOW);
          break;
        }
   }  
    vTaskDelayUntil(&xPreviousWakeTime,100/ portTICK_PERIOD_MS ); 
  }//end for
}

