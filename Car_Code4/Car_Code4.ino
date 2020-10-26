//  #include <Servo.h>

#include <Wire.h>

const int trigPin1 = 30;
const int echoPin1 = 32;
const int trigPin2 = 8;
const int echoPin2 = 9;

const int trigPin3 = 37;
const int echoPin3 = 35;
const int trigPin4 = 42;
const int echoPin4 = 40;

//  const int trig[4] = {37, 22, 8, 42};
//  const int echo[4] = {35, 24, 9, 40};

int af = 13;
int as = 12;
int bf = 7;
int bs = 6;
int pwma = 4;
int pwmb = 3;

const int inter_time = 500;
int times = 0;
int data = 1;

double distance1;
double distance2;
double distance3;
double distance4;

double ANG1;
double ANG2;
double ANG3;

double trigBetween = 20;
double wheelBetween = 50;
int T_Catch_up = 2;

float V0;
float V1_plus;
float V2_plus;

int Pa;
int Pb;
double AVGPa = 0;
double AVGPb = 0;
double toPa = 0;
double toPb = 0;

// 開關相關腳位及變數
boolean state = false;
boolean buttonUp = true;
int SwitchPin = 31;

//-----------------------------------------------SetUpIsHere--------------------------------------------------------------
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
    //  analogWrite(pwma, 60);
    //  analogWrite(pwmb, 60);
    digitalWrite(af, HIGH);
    digitalWrite(as, LOW);
    digitalWrite(bf, HIGH);
    digitalWrite(bs, LOW);

    //  開關初始設定
    pinMode(SwitchPin, INPUT);
    digitalWrite(SwitchPin, HIGH);  //  上拉電阻
}

double ping1() {
    digitalWrite(trigPin1 ,HIGH); //觸發腳位設定為高電位
    delayMicroseconds(10);   //持續5微秒
    digitalWrite(trigPin1 ,LOW);
    distance1 = pulseIn(echoPin1 ,HIGH) / 58.0;
    if (distance1 >= 250){
      return 250;  // 換算成 cm 並傳回
    }  else return  (distance1);
}


double ping2() {
    digitalWrite(trigPin2 ,HIGH); //觸發腳位設定為高電位
    delayMicroseconds(10);   //持續5微秒
    digitalWrite(trigPin2 ,LOW);
    distance2 = pulseIn(echoPin2 ,HIGH) / 58.0;
    if (distance2 >= 250){
      return 250;  // 換算成 cm 並傳回
    }  else return  (distance2);
}

double pingL() {
    digitalWrite(trigPin3 ,HIGH); //觸發腳位設定為高電位
    delayMicroseconds(10);   //持續5微秒
    digitalWrite(trigPin3,LOW) ;
    double distanceL = pulseIn(echoPin3,HIGH) / 58.0;
    if (distanceL >= 350){
      return 350  ;  // 換算成 cm 並傳回
    }  else return  (distanceL);
}

double pingR() {
    digitalWrite(trigPin4 ,HIGH); //觸發腳位設定為高電位
    delayMicroseconds(10);   //持續5微秒
    digitalWrite(trigPin4 ,LOW) ;
    double distanceR = pulseIn(echoPin4,HIGH) / 58.0;
    if (distanceR >= 350){
      return 350  ;  // 換算成 cm 並傳回
    }  else return  (distanceR);
}

double angle_data(float x, float y){
  
    Serial.begin(9600);
  
    ANG1 = acos((pow(x, 2) + pow(trigBetween, 2) - pow(y, 2)) / (2 * x * trigBetween)) * 180 / PI ;
    ANG2 = acos((pow(y, 2) + pow(trigBetween, 2) - pow(x, 2)) / (2 * y * trigBetween)) * 180 / PI ;

    distance3 = sqrt(pow(y, 2) + pow((trigBetween / 2), 2) - 2 * y * (trigBetween / 2) * cos(ANG2 / 180 * PI));
    ANG3 = acos((pow(distance3, 2) + pow((trigBetween / 2), 2) - pow(x, 2)) / (2 * distance3 * (trigBetween / 2))) * 180 / PI ;

    //  Serial.println("ANG3(未修正) = " + String(ANG3));
    
    float omega;
    
    if (ANG3 >= 90){
        ANG3 = ANG3 - 90;
        omega = ANG3 * PI / 180 / T_Catch_up;
    }else{
        ANG3 = 90 - ANG3;
        omega = ANG3 * PI / 180 / T_Catch_up * (-1);
    }

    /*
    Serial.println("角度1(L) = " + String(ANG1)); 
    Serial.println("角度2(R) = " + String(ANG2));
    Serial.println("角度3(target) = " + String(ANG3) + " 度");
    Serial.println("distance3(target) = " + String(distance3) + " (cm)");
    Serial.println("轉速 = " + String(omega) + "rad/s");
    */
    
    V1_plus = omega * wheelBetween / 2;
    V2_plus = omega * wheelBetween / 2 * (-1);
    
    /*
    Serial.println("V1_plus = " + String(V1_plus) + "(cm/s)");
    Serial.println("V2_plus = " + String(V2_plus) + "(cm/s)");
    */
}
    // 1. use pwma, pwmb 算出初始速度，let Initial value = 60，find the coefficient between V1, V2, pwmValue，藉此可知初始速度V_01, V_02
    // 2. return V_plus + V0，算出兩輪車速。
    
double Speed_Cal(){

    float VToPwm = 1.0;
    V0 = distance3 / T_Catch_up;
    
    float V1 = V0 + V1_plus;
    float V2 = V0 + V2_plus;
    Serial.println("V1 = " + String(V1));
    Serial.println("V2 = " + String(V2));

    //  VToPwm是速度換PWM值得係數，此係數還待更加精準的測量
    
    Pa = V2 * VToPwm;
    Pb = V1 * VToPwm;
    if (Pa > 80){
        Pa = 80;
    }
    if (Pb > 80){
        Pb = 80;
    }
    
    Serial.println("Pa = " + String(Pa));
    Serial.println("Pb = " + String(Pb));
    digitalWrite (af, HIGH);
    digitalWrite (bf, HIGH);
    analogWrite(pwma, (Pa + 7));
    analogWrite(pwmb, Pb);    

}

//-------------------------------------------------------------Find_Someone------------------------------------------------------------
double Find_Someone(double lastD1, double lastD2){
    Serial.println("search");

    if (lastD1 > lastD2){
      
        Pa = 0;
        Pb = 25;
        analogWrite(pwma, Pa);
        analogWrite(pwmb, Pb);
        
    }else {
      
        Pa = 25;
        Pb = 0;
        analogWrite(pwma, Pa);
        analogWrite(pwmb, Pb);
      
    }
    
    lastD1 = ping1();
    lastD2 = ping2();
    distance1 = lastD1;
    distance2 = lastD2;
    
    distance4 = abs(distance1 - distance2);
    Serial.println("NewD1 = " + String(distance1) + "NewD2 = " + String(distance2));
    delay(100);
}

void Back_Check(double x, double y){
    if (x <= 30  ||  y <= 30){
      
        digitalWrite(as, HIGH);
        digitalWrite(bs, HIGH);
        analogWrite(pwma, 47);
        analogWrite(pwmb, 40);
        Serial.println("Back");
    
    }else{ 
        digitalWrite(as, LOW);
        digitalWrite(bs, LOW);
    }  
}

void Left_Right_check(double *D1, double *D2, double DR, double DL){
    
    if(DR <= 35 && Pa <= Pb){
        Pa = Pb + 15;
        Serial.println("--------------Turn left Fixing---------------");
        Serial.println("New Pa - Pb= " + String(Pa) + "-" + String(Pb));
        Serial.println("Turn left Fixing");
        analogWrite(pwma, Pa);
        analogWrite(pwmb, Pb);
    }
    if(DL <= 35 && Pb <= Pa){
        Pb = Pa + 15;
        Serial.println("--------------Turn right Fixing-------------");
        Serial.println("New Pa - Pb= " + String(Pa) + "-" + String(Pb));
        analogWrite(pwma, Pa);
        analogWrite(pwmb, Pb);
    }
}

void Rush_Check(int Pa, int Pb){

    Serial.println("--------------RUSH CHECK-------------");
    int LastPa = Pa;
    int LastPb = Pb;
    toPa += Pa;
    toPb += Pb;
    AVGPa = toPa / times;
    AVGPb = toPb / times;
    Serial.println("次數" + String(times));
    Serial.println("AVGPa = " + String(AVGPa) + " - " + "AVGPb = " + String(AVGPb));
    /*
    double AVGPaa = AVGPa - 30;
    double AVGPbb = AVGPb - 30;
    */
    //    Try it 
    if (LastPa > (AVGPa - 30) || LastPb > (AVGPb - 30)){
        Pa = AVGPa;
        Pb = AVGPb;
    }
    analogWrite(pwma, (Pa + 7));
    analogWrite(pwmb, Pb);
}

//-----------------------------------------------------------LoopIsHere---------------------------------------------------------------------

void loop() {
  
    if(digitalRead(SwitchPin) != HIGH && buttonUp == true) {
        state = !state;
        buttonUp = false;
    } else if (digitalRead(SwitchPin) == HIGH && buttonUp != true) {
        buttonUp = true;
      }
      
    delay(10);

    if (state == false){
        Serial.println("Switch on");    
        String str1 ="";
        distance1  = ping1();
        distance2  = ping2();
        
        str1 = " Distance1=" + String(distance1) + "cm , Distance2=" + String(distance2) + " cm" ;
        Serial.println(str1) ;


        //  控制馬達的轉動方式放在這
        if (distance1 <= 40  ||  distance2 <= 40){
            /*
            if (distance1 == 0 || distance2 == 0){
                Find_Someone(distance1, distance2);
            }
            */
            digitalWrite (af, LOW); 
            digitalWrite (bf, LOW);
            Serial.println("Stop");
            Back_Check(distance1, distance2);
        
        }else{

            times += 1;
            digitalWrite (af, HIGH);
            digitalWrite (bf, HIGH);

            distance4 = abs(distance1 - distance2);
            
            while (distance4 > trigBetween){
              
                Find_Someone(distance1, distance2);
                
            }
            
            angle_data(distance1, distance2);
            Speed_Cal();
            //  Rush_Check(Pa, Pb);

            //  左右距離確認
            double distanceL = pingL();
            double distanceR = pingR();            
            Left_Right_check(&distance1, &distance2, distanceR, distanceL);
            
        }
          
        delay(inter_time);

    }else{          
        digitalWrite(af, LOW);
        digitalWrite(bf, LOW);    
    } 

}
