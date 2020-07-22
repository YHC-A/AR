void setup() {
  Serial.begin(9600);
  
  float deg=30;
  float rad=deg*PI/180;
  float x = sin(rad);
  Serial.println(x);  //輸出 0.50
  
  }
void loop() {
  
  }
