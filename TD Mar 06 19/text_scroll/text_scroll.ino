#include "U8glib.h"
 
// Constructor especifico para el display utilizado
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST);  // Dev 0, Fast I2C / TWI
 
int X_pos = 0; // posicion inicial scroll
 
void setup() {

}

//============================================================
void loop(void) {
 
  // ############## Inicio "picture loop" ####### 
   u8g.firstPage(); 
   do { 
   draw();
   } while( u8g.nextPage() ); 
  // ############## Fin "picture loop" ########## 
 
   if(X_pos > -250) X_pos--;  // posicion horizontal scroll 
   else X_pos = 0;            // cuando esta fuera de pantalla se inicia
 
}
//============================================================
 
void draw(void) {
 
 u8g.setFont(u8g_font_unifont);
 u8g.drawStr( X_pos, 15, " I2C Display OLED .96' 128x64"); // Scroll horizontal
 u8g.drawLine(0, 18, 127, 18); // linea separacion
 
 u8g.setFont(u8g_font_osb18); // cambio tipo de letra
 u8g.drawStr( 12, 44, "SSD1306"); 
 
// u8g.setFont(u8g_font_5x7); // cambio tipo de letra
 u8g.setFont(u8g_font_9x15);
 u8g.drawStr( 0, 62, "laboratorio"); 
}
