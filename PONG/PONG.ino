#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST);

int XBall = 64, YBall = 32;
const int XJ1 = 15;
int YJ1, YJ2 = 5;
const int XJ2 = 113;
int PJ1, PJ2 = 0;

const int J1 = A0;
const int J2 = A1;

void setup() {
  u8g.firstPage();
  do {  
    splash();
  } while( u8g.nextPage() );
  delay(1500);
}

void loop() {
  Ball();
  Players();
  u8g.firstPage();
  do {  
    draw();
  } while( u8g.nextPage() );

}

void draw(){
  u8g.drawBox(XBall, YBall, 2, 2);
  u8g.drawBox(XJ1, YJ1 , 2, 10);
  u8g.drawBox(XJ2, YJ2 , 2, 10);
  for(int i = 0; i<64; i+=5){
    u8g.drawVLine(64, i, 3);  
  }
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(50,60);
  u8g.print(PJ1);
  u8g.setPrintPos(70,60);
  u8g.print(PJ2);
  
}

void Players(){
  YJ1 = map(analogRead(J1), 0,1023,0,54);
  YJ2 = map(analogRead(J2), 0,1023,0,54);
}



void Ball(){
  enum StateBall {S0,S1,S2,S3};
  static StateBall state = S0;
  
  switch(state){
    case S0: // diagonal superior derecha;
      if(YBall == 0 ){
        state = S1;
      }else if(XBall == XJ2-2 && abs(YBall - (YJ2+5))<5){
        state = S3;
      }else{
        XBall++;
        YBall--;
      }
    break;
    case S1: // diagonal inferior derecha;
    if(YBall == 62){
        state = S0;
      }else if(XBall == XJ2-2 && abs(YBall - (YJ2+5))<5){
        state = S2;
      }else{
        XBall++;
        YBall++;
      }
    break;
    case S2: // diagonal inferior Izquierda;
    if(YBall == 62){
        state = S3;
      }else if(XBall == XJ1+2 && abs(YBall - (YJ1+5))<5){
        state = S1;
      }else{
        XBall--;
        YBall++;
      }
    break;
    case S3: // diagonal superior Izquierda;
    if(YBall == 0){
        state = S2;
      }else if(XBall == XJ1+2 && abs(YBall - (YJ1+5))<5){
        state = S0;
      }else{
        XBall--;
        YBall--;
      }
    break;
  }
  
  if(XBall == 0){
    PJ2++;
    XBall = 64;
    delay(1000);
    if(random(2)== 0){
      state = S1;
    }else{
      state = S0;
    }
    if(PJ2 == 10){
      PJ2 = 0;
      PJ1 = 0;
    }
  }else if(XBall == 126){
    PJ1++;
    XBall = 64;
    delay(1000);
    if(random(2)== 0){
      state = S3;
    }else{
      state = S2;
    }
    if(PJ1 == 10){
      PJ2 = 0;
      PJ1 = 0;
    }
  }
  
}

void splash(){
  u8g.setFont(u8g_font_osb18);
  u8g.setPrintPos(30,30);
  u8g.print("PONG");
  u8g.setFont(u8g_font_profont10);
  u8g.setPrintPos(20,60);
  u8g.print("Ricardo Andres Calvo");
}

