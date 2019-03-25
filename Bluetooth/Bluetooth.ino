const int led1 = 2;
const int led2 = 3;
const int led3 = 4;

int estado = 0;

void setup(){
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop(){
  if( Serial.available()>0){
    estado = Serial.read();
  }
  switch( estado){
    case 'a':
      digitalWrite(led1, HIGH);
    break;
      case'A':
    digitalWrite(led1, LOW);
    break;
    case 'b':
      digitalWrite(led2, HIGH);
    break;
    case 'B':
      digitalWrite(led2, LOW);
    break;
    case 'c':
      digitalWrite(led3, HIGH);
    break;
    case 'C':
      digitalWrite(led3, LOW);
    break;
  }
}
