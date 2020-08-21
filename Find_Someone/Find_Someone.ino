int Pa;
int Pb;

double Find_Someone(double x, double y){
  
    double lastD1 = x;
    double lastD2 = y;
    Serial.println(String(x));
    Serial.println(String(y));
    if (lastD1 >= lastD2){
      
        Pa = 0;
        Pb = 15;
        //  analogWrite(pwma, Pa);
        //  analogWrite(pwmb, Pb);
        
    }else{
      
        Pa = 15;
        Pb = 0;
        //  analogWrite(pwma, Pa);
        //  analogWrite(pwmb, Pb);
      
    }
    Serial.println(String(Pa));
    Serial.println(String(Pb));
    delay(1000);
}

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    double x = random(0, 350);
    double y = random(0, 350);
    Find_Someone(x, y);
}
