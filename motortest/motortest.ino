#include <DFRobot_TFmini.h>
SoftwareSerial mySerial(11, 10); // RX, TX


int left1 = 24;
int left2 = 23;
int leftspeed = 44;
int right1 = 27;
int right2 = 28;
int rightspeed = 45;
DFRobot_TFmini TFmini;
uint16_t distance;

void setup() {
  Serial.begin(115200);
  TFmini.begin(mySerial);
  pinMode(left1,OUTPUT);
  pinMode(left2,OUTPUT);
  pinMode(right1,OUTPUT);
  pinMode(right2,OUTPUT);
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  analogWrite(leftspeed, 150);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
  analogWrite(rightspeed, 150);
  delay(1000);
}

void loop() {
  if(TFmini.measure()){
    distance = TFmini.getDistance();       //Get distance data
    Serial.print("Distance = ");
    Serial.println(distance);
    delay(10);
    if(distance < 20){
      Serial.println("정지");
        digitalWrite(left1, LOW);
        digitalWrite(left2, LOW);
        analogWrite(leftspeed, 0);
        digitalWrite(right1, LOW);
        digitalWrite(right2, LOW);
        analogWrite(rightspeed, 0);
    }
  }
}
