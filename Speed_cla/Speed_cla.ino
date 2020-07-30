
int T_Catch_up = 2;


double Speed_Cal(){
    int SpeedToPwm = 5;
    double distance3 = random(0, 150);
    float V1_plus = random(-10, 10);
    float V2_plus = V1_plus * (-1);
    float V0 = distance3 / T_Catch_up;
    
    float V1 = V0 + V1_plus;
    float V2 = V0 + V2_plus;
    Serial.println("V1 = " + String(V1));
    Serial.println("V2 = " + String(V2));

    int Pa = V1 * SpeedToPwm;
    int Pb = V2 * SpeedToPwm;
    if (Pa > 255){
        Pa = 255;
    }
    if (Pb > 255){
        Pb = 255;
    }
    Serial.println("Pa = " + String(Pa));
    Serial.println("Pb = " + String(Pb));

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Speed_Cal();
}

void loop() {
  // put your main code here, to run repeatedly:
    Speed_Cal();
}
