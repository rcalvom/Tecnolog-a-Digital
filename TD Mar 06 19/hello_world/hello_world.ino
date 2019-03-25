#include "U8glib.h"

// Constructor especifico para el display utilizado
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST);  // Dev 0, Fast I2C / TWI

void draw() {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 22, "Hello World");
}

void setup(void) {
}

void loop(void) {
  // ############## Inicio "picture loop" ####### 
  u8g.firstPage();
  int i = 0;
  do {
  draw();
  } while( u8g.nextPage() );
  // ############## Fin "picture loop" ##########
  delay(1000);
}
