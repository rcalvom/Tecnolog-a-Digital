// the setup function runs once when you press reset or power the board
void setup() {

  //init 4 segs display
  tm1637.init();
  tm1637.set(BRIGHT_DARKEST);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  
  tm1637.display(data);
  tm1637.point(true);
  //delay(3000);
  //tm1637.displayNum(num);
}
