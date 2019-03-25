//counting display

#include "U8glib.h"

//********************************************************************************
// Change this constructor to match your display!!!
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST); // Dev 0, Fast I2C / TWI
//********************************************************************************

int a=0;

void draw(void) {
  u8g.setFont(u8g_font_profont10
  );      // select font
  u8g.setPrintPos(44,49);           // set position
  u8g.print(a);                     // display counter value
}

void setup(void) {
}

void loop(void) {
  
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );

  if(a<15) a++;
  else a=0;
  
  delay(500);  // Delay of 5sec before accessing DHT11 (min - 2sec)
}
