bool readSensor(){  //lee el sensor y retorna true si ha habido un cambio en su estado
  enum state_t {START,CAMBIO,EVALUAR,DELAY};
  static state_t state=START;  
  static bool val[2];         //val[0]:valor previo; val[1]:valor actual
  bool flag=false;
  static int contador=0;
  switch(state){
    case START:
      val[1] = digitalRead(sensorPin);
      val[0] = val[1];
      flag = false;
      state = CAMBIO;
      digitalWrite(13,LOW);
      break;
    case CAMBIO:
      val[1]= digitalRead(sensorPin);
      if(val[0] == 0 && val[1] == 1){
        state = DELAY;
        flag = true;
        digitalWrite(13,HIGH);
      }          
      val[0] = val[1];
      state = CAMBIO;
      break;
  }//end switch
  return flag;         //retornar si ha ocurrido un cambio 
}
