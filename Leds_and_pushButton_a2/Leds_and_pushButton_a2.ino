#include <Arduino_FreeRTOS.h>
#include <Button.h> 
//-----------------------------creacion de un objeto (myBtn) de la clase(Button) ---------------------------------------------------------------
#define BUTTON_PIN 2       //Connect a tactile button switch (or something similar)
                           //from Arduino pin 2 to ground.
#define PULLUP true        //To keep things simple, we use the Arduino's internal pullup resistor.
#define INVERT true        //Since the pullup resistor will keep the pin high unless the
                           //switch is closed, this is negative logic, i.e. a high state
                           //means the button is NOT pressed. (Assuming a normally open switch.)
#define DEBOUNCE_MS 20     //A debounce time of 20 milliseconds usually works well for tactile button switches.

Button myBtn(BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);    //Declare the object myBtn usando el constructor: Button(pin, puEnable, invert, dbTime);
//------------------------------------------------------------------------------------------------------------------------------------------------


// define task Leds
void TaskLeds( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {

  pinMode(4,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(8,OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect
  }                       

  // Now set up the task.
  xTaskCreate(
    TaskLeds
    ,  (const portCHAR *)"Leds"   // A descriptive name for the task. Not used by FreeRTOS in any way.
    ,  128  // Stack size (128x2=256 bytes)
    ,  NULL
    ,  1  // Priority, with 3 being the highest, and 0 being the lowest.
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

//****************************************************
//****************** Tasks ***************************

//===================================================
//================== TaskLeds1 =======================

void TaskLeds(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  /*
    TaskLeds1: Manejo de leds Rojo y Verde
  */

    enum state_type{Red,Green,Blue};
    state_type state;
    
    bool Fsm_isActive=false;

    unsigned long timeCounter=0;

  for (;;) // A Task shall never return or exit.
  { 
    if (Fsm_isActive==false){
      Fsm_isActive=true;      //activar la FSM
      state=Red;              //ir al estado Red
      outSerial("Red");
      red(HIGH);
      blue(LOW);
      green(LOW);
      //al entrar (en) al estado Red llamar la funcion outSerial, en:outSerial("Red");
    }else{
      myBtn.read();           //lee el estado del pulsador
      switch(state){
        case Red:  
          //outSerial("Red");           
          if (myBtn.wasPressed()){ //Si el pulsador ha sido pulsado
            state=Green;           //ir al estado Green
            outSerial("Green");    //al entrar (en) al estado Green llamar la funcion outSerial, en:outSerial("Green"); 
            red(LOW);
            blue(LOW);
            green(HIGH);
          }
          break;
        case Green:
          timeCounter++;                //Incrementar contador de Tiempo 
          if(timeCounter>=25){          //Si han pasado 5 o mas segundos:
            state=Blue;                 //ir a estado Blue
            timeCounter=0;              //hacer un reset del contador de tiempo
            outSerial("Blue");          //al entrar (en) al estado Red llamar la funcion outSerial, en:outSerial("Blue"); 
            red(LOW);
            blue(HIGH);
            green(LOW);
          }
          break;
        case Blue:
          timeCounter++;                //Incrementar contador de Tiempo 
          if(timeCounter>=15){          //Si han pasado 3 o mas segundos:
            state=Red;                  //ir a estado Red
            timeCounter=0;              //hacer un reset del contador de tiempo
            outSerial("Red");
            red(HIGH);
            blue(LOW);
            green(LOW);//al entrar (en) al estado Red llamar la funcion outSerial, en:outSerial("Red"); 
          }
          break; 
      }//end switch         
    }//end if
    vTaskDelay(200/ portTICK_PERIOD_MS ); // Bloquea task1 por 200 ms                                                                    
  }//end for
}//end task
//===========================================================

//**********************************************************
//****************** Functions *****************************

void outSerial(char y[]){
  Serial.println(y); 
}

void red(bool state){
  digitalWrite(4,state);
}
void blue(bool state){
  digitalWrite(8,state);
}
void green(bool state){
  digitalWrite(6,state);
}
//***********************************************************

