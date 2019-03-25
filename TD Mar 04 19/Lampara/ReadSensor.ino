bool readSensor(){  //lee el sensor y retorna true si ha habido un cambio en su estado
  enum state_t {START,CAMBIO,EVALUAR,DELAY};
  static state_t state=START;  
  static bool val[2];         //val[0]:valor previo; val[1]:valor actual
  bool chgDetected=false;
  static int contador=0;
  switch(state){
    case START:
      val[1]=digitalRead(sensorPin);  //valor actual
      val[0]=val[1];          //valor previo = valor 
      chgDetected=false;      //no se ha detectado cambio
      state=CAMBIO;           //ir a esperar cambio
      break;
    case CAMBIO:
      val[1]=digitalRead(sensorPin);  //leer valor actual del sensor
      if (val[1]!=val[0]){    //si este valor es diferente del anterior
          state=DELAY;        //realizar un delay
      }
      break;
    case DELAY:               //dealy de (100+2*100=300ms)
      contador++;         
      if (contador==2){
        state=EVALUAR;        //ir a evaluar si realmente hubo un cambio
        contador=0;
      }
      break;
    case EVALUAR:
      val[1]=digitalRead(sensorPin);  //leer de nuevo valor actual
      if (val[1]!=val[0]){    //si difernte al valor previo
          state=CAMBIO;       //ir a esperar un nuevo cambio
          chgDetected=true;   //ha habido un cambio
          val[0]=val[1];      //actualizar valor previo
      }else{
        state=CAMBIO;
      }
      break;      
          
  }//end switch
  return chgDetected;         //retornar si ha ocurrido un cambio 
}
