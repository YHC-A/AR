//  const int trigPin1 = 37;
//  const int echoPin1 = 35;
const int trigPin2 = 22;
const int echoPin2 = 24 ;

const int trigPin3 = 8;
const int echoPin3 = 9;
//  const int trigPin4 = 42;
//  const int echoPin4 = 40;


//  const int trig[4] = {37, 26, 8, 42};
//  const int echo[4] = {35, 28, 9, 40};

int af = 13;
int as = 12;
int bf = 7;
int bs = 6;
int pwma = 4;
int pwmb = 3;

float Aspeed = 60;
float Bspeed = 60;

const int inter_time = 500;
int time = 0;
int data = 1;

double distance1;
double distance2;

void setup() {
  Serial.begin(9600);
  /*
  for (int i = 0; i < 4; i++){
    pinMode (trig[i], OUTPUT);    //  超音波腳位工作模式 TRIG
    pinMode (echo[i], INPUT);     //  ............... ECHO
  }
  */
  //  pinMode (trigPin1, OUTPUT);
  //  pinMode (echoPin1, INPUT);
  pinMode (trigPin2, OUTPUT);
  pinMode (echoPin2, INPUT);
  pinMode (trigPin3, OUTPUT);
  pinMode (echoPin3, INPUT);
  //  pinMode (trigPin4, OUTPUT);
  //  pinMode (echoPin4, INPUT);
  
  //  模塊角位工作模式
  pinMode (af, OUTPUT);
  pinMode (as, OUTPUT);
  pinMode (bf, OUTPUT);
  pinMode (bs, OUTPUT);  
  
  //  馬達初始轉速 (往前), (速度60)
  analogWrite(pwma, Aspeed);
  analogWrite(pwmb, Bspeed);
  digitalWrite(af, HIGH);
  digitalWrite(as, LOW);
  digitalWrite(bf, HIGH);
  digitalWrite(bs, LOW);
}

unsigned long ping1() {
    digitalWrite(trigPin2,HIGH) ; //觸發腳位設定為高電位
    delayMicroseconds(10);   //持續5微秒
    digitalWrite(trigPin2,LOW) ;
    distance1 = pulseIn(echoPin2,HIGH)/58;
    
    if (distance1 >= 300){
      return 300  ;  // 換算成 cm 並傳回
    }  else return  (distance1);
    
}


unsigned long ping2() {
    digitalWrite(trigPin3,HIGH) ; //觸發腳位設定為高電位
    delayMicroseconds(10);   //持續5微秒
    digitalWrite(trigPin3,LOW) ;
    distance2 = pulseIn(echoPin3,HIGH)/58;
    
    if (distance2 >= 300){
      return 300  ;  // 換算成 cm 並傳回
    }  else return  (distance2);
    
}
  
void turn(){
    if (distance1 > distance2 && Aspeed >= 50){
        Aspeed -= 0.2;
        Bspeed += 0.2;
        if (Bspeed >= 70){
            Bspeed = 70;
        }
    }
    
    if (distance1 < distance2 && Bspeed >= 50){
        Aspeed += 0.5;
        Bspeed -= 0.5;
        if (Aspeed >= 70){
            Aspeed = 70;
        }
    }

    analogWrite(pwma, Aspeed);
    analogWrite(pwmb, Bspeed);    
}


void loop() {
    String str1 = "";
    String str2 = "";
    distance1  = ping1()  ;
    distance2  = ping2()  ;
    str1 = " Distance1=" + String(distance1) + "cm , Distance2=" + String(distance2) + " cm" ;
    Serial.println(str1) ;
    str2 = "A = " + String(Aspeed) + "  " + "B = " + String(Bspeed);
    Serial.println(str2) ;

    
    //  控制馬達的轉動方式放在這
    if (distance1 <= 40  ||  distance2 <= 40){
        digitalWrite (af, LOW);
        digitalWrite (bf, LOW);
    } else {
        digitalWrite (af, HIGH);
        digitalWrite (bf, HIGH);
      }

    turn();
    
    Serial.println(digitalRead(af));
    Serial.println(digitalRead(bf));

    delay(100) ;
}
