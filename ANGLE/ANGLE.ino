void setup() {
  Serial.begin(9600);
  
  double distance1 = 38;
  double distance2 = 40;
  float trigBetween = 4.5;
  
  double ANG1 = acos((distance1 * distance1 + trigBetween * trigBetween - distance2 * distance2) / (2 * distance1 * trigBetween)) * 180 / PI ;
  double ANG2 = acos((distance2 * distance2 + trigBetween * trigBetween - distance1 * distance1) / (2 * distance2 * trigBetween)) * 180 / PI ;
  double ANG3 = acos((distance1 * distance1 + distance2 * distance2 - trigBetween * trigBetween) / (2 * distance2 * distance1)) * 180 / PI ;
  
  /*
  float deg=30;
  float rad=deg*PI/180;
  float x = sin(rad);
  */
  
  Serial.println(ANG1);  //輸出 0.50
  Serial.println(ANG2);
  Serial.println(ANG3);
  
  }
void loop() {
  
  }
