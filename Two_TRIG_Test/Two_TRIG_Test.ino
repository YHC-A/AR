void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()) {
    int num = Serial.parseInt();
    Serial.print(num);
  }
  Serial.println("Hello World");
}
