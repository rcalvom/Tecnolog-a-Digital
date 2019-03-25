// moving_box 

#include "U8glib.h"

//********************************************************************************
// Change this constructor to match your display!!!
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST); // Dev 0, Fast I2C / TWI
//********************************************************************************

int xPos = 128-20;

void setup() {  
}

void loop() {  
  enum state_type {backward,forward};
  static state_type state=backward;
  
  u8g.firstPage();
  do {  
    draw();
  } while( u8g.nextPage() );

  switch(state){
    case backward:
      if(xPos>0) xPos--;
      else state=forward;
      break;
    case forward:
      if(xPos<126-20) xPos++;
      else state=backward;
      break;      
  }
}  
void draw(){
  u8g.drawBox(xPos,12,20,20); 
}
