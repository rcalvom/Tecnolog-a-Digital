#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#include "queue.h"

#include <TimerOne.h> //para manejar interrupcion por Timer1
#include "TM1637.h"   //para manejar display 7 segs 4 digitos
#define ON 1
#define OFF 0


#include <Button.h> 
//-----------------------------creacion de objetos de la clase(Button) ---------------------------------------------------------------     
#define RESET_PIN 4  
#define ALARM_PIN 5 
#define MIN_PIN 6 
#define HOUR_PIN 7

#define PULLUP true        //To keep things simple, we use the Arduino's internal pullup resistor.
#define INVERT true        //Since the pullup resistor will keep the pin high unless the
                           //switch is closed, this is negative logic, i.e. a high state
                           //means the button is NOT pressed. (Assuming a normally open switch.)
#define DEBOUNCE_MS 20     //A debounce time of 20 milliseconds usually works well for tactile button switches.

Button BtnReset(RESET_PIN, PULLUP, INVERT, DEBOUNCE_MS);    //Declare the objects usando el constructor: Button(pin, puEnable, invert, dbTime);
//------------------------------------------------------------------------------------------------------------------------------------------------

//para counter
unsigned int counter=0;
int8_t CounterDisp[] = {0x00,0x00,0x00,0x00};
unsigned char Update;
bool flagReset=false;

#define CLK 2 //pins definitions for TM1637 and can be changed to other ports
#define DIO 3
TM1637 tm1637(CLK,DIO);

// define tasks ;
void TaskCounter( void *pvParameters );
void TaskButtons(void *pvParameters);




