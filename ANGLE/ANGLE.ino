double distance1 = 100;
double distance2 = 96;
double distance3;
double trigBetween = 10;
double wheelBetween = 60;
int T_Catch_up = 2;

//  以上單位為 cm, sec

int angle_date(float x, float y){
  Serial.begin(9600);
  
  double ANG1 = acos((pow(distance1, 2) + pow(trigBetween, 2) - pow(distance2, 2)) / (2 * distance1 * trigBetween)) * 180 / PI ;
  double ANG2 = acos((pow(distance2, 2) + pow(trigBetween, 2) - pow(distance1, 2)) / (2 * distance2 * trigBetween)) * 180 / PI ;

  distance3 = sqrt(pow(distance2, 2) + pow((trigBetween / 2), 2) - 2 * distance2 * (trigBetween / 2) * cos(ANG2 / 180 * PI));

  double ANG3 = acos((pow(distance3, 2) + pow((trigBetween / 2), 2) - pow(distance1, 2)) / (2 * distance3 * (trigBetween / 2))) * 180 / PI ;
  if (ANG3 >= 90){
      ANG3 = ANG3 - 90;
  } else{
      ANG3 = 90 - ANG3;
  }

  
  Serial.println("角度1(L) = " + String(ANG1)); 
  Serial.println("角度2(R) = " + String(ANG2));
  Serial.println("角度3(target, 單位 : 度) = " + String(ANG3));
  Serial.println("distance3(target, 單位 : cm) = " + String(distance3));
  
  
}


void setup() {
  angle_date(distance1, distance2);
  
  }
void loop() {
  
  }
