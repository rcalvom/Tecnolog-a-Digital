void TaskLedRGB(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  TickType_t xPreviousWakeTime;
  xPreviousWakeTime = xTaskGetTickCount();

  enum state_type{Red, Green, Blue, Yellow, Magenta, Cyan, White, Random1 ,Random2, Off};
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
      state = Random1;
      state1 = Random1;
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
          case Red:
            digitalWrite(RED,HIGH);
            digitalWrite(GREEN,LOW);
            digitalWrite(BLUE,LOW);
            if(count > 9){
              count = 0;
              state = Green;
              state1 = Green;
            }
          break;                         
          case Green:
            digitalWrite(RED,LOW);
            digitalWrite(GREEN,HIGH);
            digitalWrite(BLUE,LOW);
            if(count > 9){
              count = 0;
              state = Blue;
              state1 = Blue;
            }
          break;
          case Blue:
            digitalWrite(RED,LOW);
            digitalWrite(GREEN,LOW);
            digitalWrite(BLUE,HIGH);
            if(count > 9){
              count = 0;
              state = Yellow;
              state1 = Yellow;
            }
          break;
          case Yellow:
            digitalWrite(RED,HIGH);
            digitalWrite(GREEN,HIGH);
            digitalWrite(BLUE,LOW);
            if(count > 9){
              count = 0;
              state = Magenta;
              state1 = Magenta;
            }
          break;
          case Magenta:
            digitalWrite(RED,HIGH);
            digitalWrite(GREEN,LOW);
            digitalWrite(BLUE,HIGH);
            if(count > 9){
              count = 0;
              state = Cyan;
              state1 = Cyan;
            }
          break;
          case Cyan:
            digitalWrite(RED,LOW);
            digitalWrite(GREEN,HIGH);
            digitalWrite(BLUE,HIGH);
            if(count > 9){
              count = 0;
              state = White;
              state1 = White;
            }
          break;
          case White:
            digitalWrite(RED,HIGH);
            digitalWrite(GREEN,HIGH);
            digitalWrite(BLUE,HIGH);
            if(count > 9){
              count = 0;
              state = Random1;
              state1 = Random1;
            }
          break;
          case Random1:
            do{
              rgb[0] = random(0,2);
              rgb[1] = random(0,2);
              rgb[2] = random(0,2);
            }while((rgb[0]+rgb[1]+rgb[2]) == 0);
            if(count1 == 0){
              digitalWrite(RED,rgb[0]);
              digitalWrite(GREEN,rgb[1]);
              digitalWrite(BLUE,rgb[2]);
            }

            if(count1 < 3){
              count1++;
            }else{
              count1=0;
            }
            if(count > 9){
              count = 0;
              count1 = 0;
              state = Random2;
              state1 = Random2;
            }
          break;
          case Random2:
            do{
              rgb[0] = random(0,2);
              rgb[1] = random(0,2);
              rgb[2] = random(0,2);
            }while((rgb[0]+rgb[1]+rgb[2]) == 0);
            if(count1 == 0){
              digitalWrite(RED,rgb[0]);
              digitalWrite(GREEN,rgb[1]);
              digitalWrite(BLUE,rgb[2]);
            }

            if(count1 < 14){
              count1++;
            }else{
              count1=0;
            }
            if(count > 9){
              count = 0;
              count1 = 0;
              state = Red;
              state1 = Red;
            }
          break;
          case Off:
            digitalWrite(RED,LOW);
            digitalWrite(GREEN,LOW);
            digitalWrite(BLUE,LOW);
          break;
        }
   }  
    vTaskDelayUntil(&xPreviousWakeTime,100/ portTICK_PERIOD_MS ); 
  }//end for
  
}
//===========================================================

