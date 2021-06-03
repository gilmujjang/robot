#include <DFRobot_TFmini.h>
#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(11,10); // RX, TX
Servo servo01;
Servo servo02;
Servo servo04;
Servo servo05;
int servo1PPos, servo2PPos, servo4PPos, servo5PPos;
int index = 0;
int servo1Pos = 0;
int servo2Pos = 0;
int servo4Pos = 0;
int servo5Pos = 0;
DFRobot_TFmini  TFmini;
uint16_t distance, strength;   // 거리와 강도를 담는 변수

void setup() {
  Serial.begin(115200);
  TFmini.begin(mySerial);
  servo01.attach(5);
  servo02.attach(6);    
  servo04.attach(8);
  servo05.attach(9);
  servo01.write(180);
  servo02.write(60);
  servo04.write(150);
  servo05.write(60);
  Serial.println("시작");
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
    if( 15>distance && distance>10 ){
      servo01.write(90);
      delay(500);
      servo02.write(90);
      delay(500);
      servo04.write(180);
      delay(500);
      servo05.write(20);
      Serial.println("잡기");
    } else {
      servo01.write(180);
      servo02.write(60);
      servo04.write(150);
      Serial.println("대기");
    }
  }
}
