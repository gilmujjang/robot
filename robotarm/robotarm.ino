#include <Servo.h>
#include <SoftwareSerial.h>

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


void setup() {
  Serial.begin(9600);
  servo01.attach(5);
  servo02.attach(6);    
  servo04.attach(8);
  servo05.attach(9);
  servo1PPos = 180;
  servo01.write(servo1PPos);
  servo2PPos = 60;
  servo02.write(servo2PPos);
  servo4PPos = 150;
  servo04.write(servo4PPos);
  servo5PPos = 60;
  servo05.write(servo5PPos);
  Serial.println("시작");

}

void loop() {
  char data;
  if(Serial.available() > 0){
    data = Serial.read();
    if(data == 'a'){
      servo1Pos = 90;
      servo2Pos = 90;
      servo4Pos = 180;
      servo5Pos = 20;
      Serial.println("잡기");
    }
    if(data == 'b'){
      servo1Pos = 180;
      servo2Pos = 60;
      servo4Pos = 150;
      Serial.println("대기");
    }
    if(data == 'c'){
      servo1Pos = 90;
      servo2Pos = 90;
      servo4Pos = 180;
      servo5Pos = 100;
      Serial.println("놓기");
    }
    //motor1 Waist
    if (servo1PPos > servo1Pos) {
      for ( int j = servo1PPos; j >= servo1Pos; j--) {   // Run servo down
        servo01.write(j);
        delay(10);    // defines the speed at which the servo rotates
      }
    }    
    if (servo1PPos < servo1Pos) {
      for ( int j = servo1PPos; j <= servo1Pos; j++) {   // Run servo up
        servo01.write(j);
        delay(10);
      }
    }
    servo1PPos = servo1Pos;   // set current position as previous position

    //motor2 Shoulder
    if (servo2PPos > servo2Pos) {
      for ( int j = servo2PPos; j >= servo2Pos; j--) {
        servo02.write(j);
        delay(10);
      }
    }
    if (servo2PPos < servo2Pos) {
      for ( int j = servo2PPos; j <= servo2Pos; j++) {
        servo02.write(j);
        delay(10);
      }
    }
    servo2PPos = servo2Pos;
      
    //motor4 Wrist Roll
    if (servo4PPos > servo4Pos) {
      for ( int j = servo4PPos; j >= servo4Pos; j--) {
        servo04.write(j);
        delay(10);
      }
    }
    if (servo4PPos < servo4Pos) {
      for ( int j = servo4PPos; j <= servo4Pos; j++) {
        servo04.write(j);
        delay(10);
      }
    }
    servo4PPos = servo4Pos;
    
    //motor5 Wrist Pitch
    if (servo5PPos > servo5Pos) {
      for ( int j = servo5PPos; j >= servo5Pos; j--) {
        servo05.write(j);
        delay(30);
      }
    }
    if (servo5PPos < servo5Pos) {
      for ( int j = servo5PPos; j <= servo5Pos; j++) {
        servo05.write(j);
        delay(30);
      }
    }
    servo5PPos = servo5Pos;
  }
}
