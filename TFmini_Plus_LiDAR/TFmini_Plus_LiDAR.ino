

#include <DFRobot_TFmini.h>

SoftwareSerial mySerial(11,10); // RX, TX

DFRobot_TFmini  TFmini;
uint16_t distance, strength;   // 거리와 강도를 담는 변수

void setup() {
  Serial.begin(115200);
  Serial.print("asdf");
  TFmini.begin(mySerial);
}

void loop() {
  if (TFmini.measure()) {
    // 거리와 신호의 강도를 측정합니다. 성공하면 을 반환하여 if문이 작동합니다.
    distance = TFmini.getDistance();       // 거리값을 mm단위로 불러옵니다.
    strength = TFmini.getStrength();       // 신호의 강도를 불러옵니다. 측정 대상이 넓으면 강도가 커집니다.
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println("cm");
    Serial.print("Strength = ");
    Serial.println(strength);
  }
  delay(100);
}
