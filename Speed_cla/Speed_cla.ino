double distance3 = 100;
int T_Catch_up = 2;
float V1_plus = 7;
float V2_plus = -7;

double Speed_Cal(){
  
    float V0 = distance3 / T_Catch_up;
    
    float V1 = V0 + V1_plus;
    float V2 = V0 + V2_plus;
    Serial.println("V1 = " + String(V1));
    Serial.println("V2 = " + String(V2));

    int Pa = V1 * 5;
    int Pb = V2 * 5;
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

}
