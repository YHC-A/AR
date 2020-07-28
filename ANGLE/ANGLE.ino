double distance1 = 100;
double distance2 = 96;
//  以上單位為 cm, sec

int angle_data(float x, float y){

  double trigBetween = 10;
  double wheelBetween = 60;
  int T_Catch_up = 2;
  double distance3;
  
  Serial.begin(9600);
  
  double ANG1 = acos((pow(x, 2) + pow(trigBetween, 2) - pow(y, 2)) / (2 * x * trigBetween)) * 180 / PI ;
  double ANG2 = acos((pow(y, 2) + pow(trigBetween, 2) - pow(x, 2)) / (2 * y * trigBetween)) * 180 / PI ;

  distance3 = sqrt(pow(y, 2) + pow((trigBetween / 2), 2) - 2 * y * (trigBetween / 2) * cos(ANG2 / 180 * PI));

  double ANG3 = acos((pow(distance3, 2) + pow((trigBetween / 2), 2) - pow(x, 2)) / (2 * distance3 * (trigBetween / 2))) * 180 / PI ;
  if (ANG3 >= 90){
      ANG3 = ANG3 - 90;
  } else{
      ANG3 = 90 - ANG3;
  }

  
  Serial.println("角度1(L) = " + String(ANG1)); 
  Serial.println("角度2(R) = " + String(ANG2));
  Serial.println("角度3(target, 單位 : 度) = " + String(ANG3));
  Serial.println("distance3(target, 單位 : cm) = " + String(distance3));

  float omega = ANG3 * PI / 180 / T_Catch_up;

  Serial.println("轉速 = " + String(omega) + "rad/s");

  float V1_plus = omega * wheelBetween / 2;
  float V2_plus = omega * wheelBetween / 2 * (-1);

  Serial.println("V1_plus = " + String(V1_plus));
  Serial.println("V2_plus = " + String(V2_plus));
  Serial.println("-------------------------------");
}


void setup() {
  
  angle_data(distance1, distance2);
  
  }
void loop() {
  
  }
