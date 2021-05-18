//腳位trig    37, 26, 8,  42
//   echo     35, 28, 9, 40
const int  trigPin1 = 12 ;  // 一號超音波 觸發腳Trig
const int  echoPin1 = 11 ;  //一號超音波 接收腳 Echo
unsigned long distance1 ; // 距離 cm

const int  trigPin2 = 3 ;   //二號超音波 觸發腳Trig
const int  echoPin2 = 2 ;   //二號超音波 接收腳 Echo
unsigned long distance2 ; // 距離 cm

unsigned long ping1() {
    digitalWrite(trigPin1,HIGH) ; //觸發腳位設定為高電位
    delayMicroseconds(10);   //持續5微秒
    digitalWrite(trigPin1,LOW) ;
    distance1 = pulseIn(echoPin1,HIGH)/58;
    if (distance1 >= 250){
      return 0  ;  // 換算成 cm 並傳回
    }  else return  (distance1);
  }


unsigned long ping2() {
    digitalWrite(trigPin2,HIGH) ; //觸發腳位設定為高電位
    delayMicroseconds(10);   //持續5微秒
    digitalWrite(trigPin2,LOW) ;
    distance2 = pulseIn(echoPin2,HIGH)/58;
    if (distance2 >= 250){
      return 0  ;  // 換算成 cm 並傳回
    }  else return  (distance2);
  }
  
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin1,OUTPUT) ;
  pinMode(echoPin1 , INPUT) ;

  pinMode(trigPin2,OUTPUT) ;
  pinMode(echoPin2 , INPUT) ;
  Serial.begin(9600) ;
}

void loop() {
  // put your main code here, to run repeatedly:
    String str1 ="";
    distance1  = ping1()  ;
    distance2  = ping2()  ;
    str1 = "son1=" + String(distance1) + "cm , son2=" + String(distance2) + " cm" ;
    Serial.println(str1) ;
    if (distance1 <= 100  ||  distance2 <= 100){
        Serial.println("__________Stop__________");
    } else {
          Serial.println("_______Keep Going_______");
      }
    delay(100) ;
}
