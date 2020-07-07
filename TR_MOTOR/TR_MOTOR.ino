void setup() {
  pinMode(7 ,OUTPUT);
  pinMode(6 ,OUTPUT);
  pinMode(5 ,OUTPUT);
  pinMode(4 ,OUTPUT);
}

void loop() {
    
    digitalWrite(7,HIGH);
    digitalWrite(4,HIGH);
    analogWrite(6,200);
    analogWrite(5,200);
  
}
