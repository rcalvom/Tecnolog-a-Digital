void setup() {
  Serial.begin(9600);  
  while (!Serial) {
  }
  Serial.flush();
}

void loop() {
  Serial.println(map(analogRead(A0),0,1023,0,500)/100.0);

}
