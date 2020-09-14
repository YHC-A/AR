#include <NewPing.h>
#define TRIG_PIN    12          // trigger Pin
#define ECHO_PIN    11          // Echo Pin
#define MAX_DISTANCE 200        // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);    // 設定 NewPing 物件，並給與最遠測試距離

void setup() {
  Serial.begin(9600);         // 開啟串列埠顯示 ping 的距離值
}

void loop() {
  delay(50);                        // 等待 50 毫秒，需大於前程式說明的 29 秒
  unsigned int uS = sonar.ping();   // 送出 ping，並取得微秒 microseconds(uS) 時間
  Serial.print("Ping: ");
  Serial.print(sonar.convert_cm(uS));    // 換算時間為公分，如顯示 0，表示超出距離範圍
  Serial.println("cm");
}
