double distance1;
double distance2;
double distance3;
double distance4;
double distance5;
double distance6;

void setup() {
  Serial.begin(9600);
 
}

void loop() {
    
    String str1 = "";
    double distance1 = random(0, 350);
    double distance2 = random(0, 350);
        
    str1 = "Distance1=" + String(distance1) + "cm , Distance2=" + String(distance2) + " cm" ;
    Serial.println(str1) ;
        
    distance4 = distance1 - distance2;
    Serial.println(distance4);
    double distance5 = (distance1 + distance2) / 2;
    Serial.println(distance5) ;
    
    if (distance4 >= 20){
        Serial.println("Re1");
        distance1 = distance5 + 7.5;
        distance2 = distance5 - 7.5;
    }
    if (distance4 <= -20){
        Serial.println("Re2");
        distance1 = distance5 - 7.5;
        distance2 = distance5 + 7.5;
    }
    
    str1 = "Distance1=" + String(distance1) + "cm , Distance2=" + String(distance2) + " cm" ;
    Serial.println(str1) ;
        
    delay(1000);        

  
}
