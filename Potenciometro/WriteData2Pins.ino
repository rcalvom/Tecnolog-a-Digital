void writeData2Pins(int pins[]){
  //escribe los bits de dout.value a los pines de salida
  digitalWrite(pins[0],dout.rawdata.b0);
  digitalWrite(pins[1],dout.rawdata.b1);
  digitalWrite(pins[2],dout.rawdata.b2);
  digitalWrite(pins[3],dout.rawdata.b3);
  digitalWrite(pins[4],dout.rawdata.b4);
  digitalWrite(pins[5],dout.rawdata.b5);
  digitalWrite(pins[6],dout.rawdata.b6);
  digitalWrite(pins[7],dout.rawdata.b7);  
 }

 int Potencia(int a, int b){
  if(b==0){
    return 1;
  }else{
    return Potencia(a,b-1)*a;
  }
 }
