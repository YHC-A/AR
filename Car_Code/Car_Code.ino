const int trigPin1 = 37;
const int echoPin1 = 35;
const int trigPin2 = 26;
const int echoPin2 = 28;

const int trigPin3 = 8;
const int echoPin3 = 9;
const int trigPin4 = 42;
const int echoPin4 = 40;

//  const int trig[4] = {37, 26, 8, 42};
//  const int echo[4] = {35, 28, 9, 40};

int af = 13;
int as = 12;
int bf = 7;
int bs = 6;
int pwma = 4;
int pwmb = 3;

const int inter_time = 500;
int time = 0;
int data = 1;

double distance1;
double distance2;
double distance3;

double ANG1;
double ANG2;
double ANG3;

double trigBetween = 10;
double wheelBetween = 60;
int T_Catch_up = 2;

float V0;
float V1_plus;
float V2_plus;

int Pa;
int Pb;

//-----------------------------SetUpIsHere--------------------------------------------------------------
void setup() {
    Serial.begin(9600);
    /*
    for (int i = 0; i < 4; i++){
      pinMode (trig[i], OUTPUT);    //  超音波腳位工作模式 TRIG
      pinMode (echo[i], INPUT);     //  ............... ECHO
    }
    */
    pinMode (trigPin1, OUTPUT);
    pinMode (echoPin1, INPUT);
    pinMode (trigPin2, OUTPUT);
    pinMode (echoPin2, INPUT);
    pinMode (trigPin3, OUTPUT);
    pinMode (echoPin3, INPUT);
    pinMode (trigPin4, OUTPUT);
    pinMode (echoPin4, INPUT);
  
    //  模塊角位工作模式
    pinMode (af, OUTPUT);
    pinMode (as, OUTPUT);
    pinMode (bf, OUTPUT);
    pinMode (bs, OUTPUT);  
  
    //  馬達初始轉速 (往前), (速度60)
    analogWrite(pwma, 60);
    analogWrite(pwmb, 60);
    digitalWrite(af, HIGH);
    digitalWrite(as, LOW);
    digitalWrite(bf, HIGH);
    digitalWrite(bs, LOW);
}

double ping1() {
    digitalWrite(trigPin1,HIGH) ; //觸發腳位設定為高電位
    delayMicroseconds(10);   //持續5微秒
    digitalWrite(trigPin1,LOW) ;
    distance1 = pulseIn(echoPin1,HIGH)/58;
    if (distance1 >= 250){
      return 0  ;  // 換算成 cm 並傳回
    }  else return  (distance1);
}


double ping2() {
    digitalWrite(trigPin2,HIGH) ; //觸發腳位設定為高電位
    delayMicroseconds(10);   //持續5微秒
    digitalWrite(trigPin2,LOW) ;
    distance2 = pulseIn(echoPin2,HIGH)/58;
    if (distance2 >= 250){
      return 0  ;  // 換算成 cm 並傳回
    }  else return  (distance2);
}

double angle_data(float x, float y){
  
    Serial.begin(9600);
  
    ANG1 = acos((pow(distance1, 2) + pow(trigBetween, 2) - pow(distance2, 2)) / (2 * distance1 * trigBetween)) * 180 / PI ;
    ANG2 = acos((pow(distance2, 2) + pow(trigBetween, 2) - pow(distance1, 2)) / (2 * distance2 * trigBetween)) * 180 / PI ;

    distance3 = sqrt(pow(distance2, 2) + pow((trigBetween / 2), 2) - 2 * distance2 * (trigBetween / 2) * cos(ANG2 / 180 * PI));

    ANG3 = acos((pow(distance3, 2) + pow((trigBetween / 2), 2) - pow(distance1, 2)) / (2 * distance3 * (trigBetween / 2))) * 180 / PI ;
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

    V1_plus = omega * wheelBetween / 2;
    V2_plus = omega * wheelBetween / 2 * (-1);

    Serial.println(V1_plus);
    Serial.println(V2_plus);

    // 這邊要用pwma, pwmb 算出初始速度，上面的初始值設定為60，找出速度對pwm的關係，藉此可知初始速度V_01, V_02
    // 接著用return 回傳V_plus + V0，藉此算出兩輪車速。
}

double Speed_Cal(){
  
    V0 = distance3 / T_Catch_up;
    
    float V1 = V0 + V1_plus;
    float V2 = V0 + V2_plus;
    Serial.println("V1 = " + String(V1));
    Serial.println("V2 = " + String(V2));

    Pa = V1 * 5;
    Pb = V2 * 5;
    if (Pa > 255){
        Pa = 255;
    }
    if (Pb > 255){
        Pb = 255;
    }
    Serial.println("Pa = " + String(Pa));
    Serial.println("Pb = " + String(Pb));

    analogWrite(pwma, Pa);
    analogWrite(pwmb, Pb);    

}
  
//-----------------------------LoopIsHere----------------------------------------------------------------

void loop() {
    
    String str1 ="";
    distance1  = ping1()  ;
    distance2  = ping2()  ;
    str1 = " Distance1=" + String(distance1) + "cm , Distance2=" + String(distance2) + " cm" ;
    Serial.println(str1) ;
    
    //  控制馬達的轉動方式放在這
    if (distance1 <= 50  ||  distance2 <= 50){
      
        digitalWrite (af, LOW);
        digitalWrite (bf, LOW);
    
    } else {
      
        digitalWrite (af, HIGH);
        digitalWrite (bf, HIGH);
        
        angle_data(distance1, distance2);
        Speed_Cal();
        
      }

    delay(100) ;
}
