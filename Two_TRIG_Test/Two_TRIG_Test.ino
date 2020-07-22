const int trigPin2 = 4;
const int echoPin2 = 5 ;

const int trigPin3 = 8;
const int echoPin3 = 9;

float distance1 = 0;
float distance2 = 0;
float t1 = 0;
float t2 = 0;

float ping1() {
    digitalWrite(trigPin2,HIGH) ; //觸發腳位設定為高電位
    delayMicroseconds(10);   //持續5微秒
    digitalWrite(trigPin2,LOW) ;
    t1 = pulseIn(echoPin2,HIGH);
    distance1 = t1 / 58.2;
    
    if (distance1 >= 300){
      return 300  ;  // 換算成 cm 並傳回
    }  else return  (distance1);
    
}

float ping2() {
    digitalWrite(trigPin3,HIGH) ; //觸發腳位設定為高電位
    delayMicroseconds(10);   //持續5微秒
    digitalWrite(trigPin3,LOW) ;
    t2 = pulseIn(echoPin3,HIGH);
    distance2 = t2 / 58.2;
    
    if (distance2 >= 300){
      return 300  ;  // 換算成 cm 並傳回
    }  else return  (distance2);
    
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (trigPin2, OUTPUT);
  pinMode (echoPin2, INPUT);
  pinMode (trigPin3, OUTPUT);
  pinMode (echoPin3, INPUT);
}



void loop() {
  // put your main code here, to run repeatedly:
    String str1 = "";
    String str2 = "";
    distance1  = ping1()  ;
    distance2  = ping2()  ;
    str1 = " Distance1=" + String(distance1) + "cm , Distance2=" + String(distance2) + " cm" ;
    Serial.println(distance1) ;

}
