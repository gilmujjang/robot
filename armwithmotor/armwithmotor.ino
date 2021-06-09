#include <DFRobot_TFmini.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <Pixy2.h>

SoftwareSerial mySerial(11, 10); // RX, TX
DFRobot_TFmini TFmini;
uint16_t distance;

Servo servo02;
Servo servo03;
Servo servo05;
Servo servo06;
Pixy2 pixy;

int servo2Pos, servo3Pos, servo5Pos, servo6Pos; // current position
int servo2PPos, servo3PPos, servo5PPos, servo6PPos; // previous position
int left1 = 24;
int left2 = 23;
int leftspeed = 44;
int right1 = 27;
int right2 = 28;
int rightspeed = 45;

int speedDelay = 20;
int index = 0;
String dataIn = "";


void setup() {
  Serial.begin(115200);
  TFmini.begin(mySerial);
  servo02.attach(5);
  servo03.attach(6);
  servo05.attach(8);
  servo06.attach(9);
  delay(500);
  Serial.println("로봇팔 시동");
  servo2PPos = 180;
  servo02.write(servo2PPos);
  servo3PPos = 90;
  servo03.write(servo3PPos);
  servo5PPos = 100;
  servo05.write(servo5PPos);
  servo6PPos = 70;
  servo06.write(servo6PPos);
  Serial.println("로봇팔 정위치");
  delay(500);
  servo02.detach();
  servo03.detach();
  servo05.detach();
  servo06.detach();
  Serial.println("로봇팔 시동 종료");
  delay(500);
  Serial.println("방향 조정 시작");
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  digitalWrite(left1, LOW);
  digitalWrite(left2, LOW);
  analogWrite(leftspeed, 0);
  digitalWrite(right1, LOW);
  digitalWrite(right2, LOW);
  analogWrite(rightspeed, 0);
  pixy.init();
}


void loop(){  
  Serial.println("루프문 시작");
  while(1){
    int i;
    pixy.ccc.getBlocks();
    if (pixy.ccc.numBlocks){
      Serial.print("Detected ");
      Serial.println(pixy.ccc.numBlocks);
      for (i=0; i<pixy.ccc.numBlocks; i++){
        Serial.print("  block ");
        Serial.print(i);
        Serial.print(": ");
        pixy.ccc.blocks[i].print();
      }
      if(pixy.ccc.blocks[0].m_x < 200){
        //좌회전
        Serial.println("좌회전");
        digitalWrite(left1, LOW);
        digitalWrite(left2, HIGH);
        analogWrite(leftspeed, 120);
        digitalWrite(right1, HIGH);
        digitalWrite(right2, LOW);
        analogWrite(rightspeed, 120);
        delay(100);
      }
      if(pixy.ccc.blocks[0].m_x > 240){
        //우회전
        Serial.println("우회전");
        digitalWrite(left1, HIGH);
        digitalWrite(left2, LOW);
        analogWrite(leftspeed, 120);
        digitalWrite(right1, LOW);
        digitalWrite(right2, HIGH);
        analogWrite(rightspeed, 120);
        delay(100);
      }
  //    라이다로 쟀을떄 멀면 전진
      if(TFmini.measure()){
        distance = TFmini.getDistance();       //Get distance data
        Serial.print("Distance = ");
        Serial.println(distance);
        delay(10);
        if(distance<10){
          Serial.println("정지");
          digitalWrite(left1, LOW);
          digitalWrite(left2, LOW);
          analogWrite(leftspeed, 0);
          digitalWrite(right1, LOW);
          digitalWrite(right2, LOW);
          analogWrite(rightspeed, 0);
          delay(1000);
          get(70,60,170,10);
          delay(1000);
          break;
        }
        else if(distance>20){
          Serial.println("전진");
          digitalWrite(left1, HIGH);
          digitalWrite(left2, LOW);
          analogWrite(leftspeed, 120);
          digitalWrite(right1, HIGH);
          digitalWrite(right2, LOW);
          analogWrite(rightspeed, 120);
          delay(100);
        }
      }                
    } else if{
      Serial.println("픽시 연결안됨");
    }
  }
//  up(180,90,100,10);
//  delay(1000);
}


void get(int a,int b,int c,int d){
  servo02.attach(5);
  servo03.attach(6);
  servo05.attach(8);
  servo06.attach(9);
  servo2Pos = a;
  servo3Pos = b;
  servo5Pos = c;
  servo6Pos = d;

  if (servo5PPos > servo5Pos) {
      for ( int j = servo5PPos; j >= servo5Pos; j--) {
        servo05.write(j);
        delay(10);
      }
   }
   if (servo5PPos < servo5Pos) {
      for ( int j = servo5PPos; j <= servo5Pos; j++) {
        servo05.write(j);
        delay(10);
      }
    }
    servo5PPos = servo5Pos;

  if (servo3PPos > servo3Pos) {
    for ( int j = servo3PPos; j >= servo3Pos; j--) {
      servo03.write(j);
      delay(10);
    }
  }
  if (servo3PPos < servo3Pos) {
    for ( int j = servo3PPos; j <= servo3Pos; j++) {
      servo03.write(j);
      delay(10);
    }
  }
  servo3PPos = servo3Pos;
           
  if (servo2PPos > servo2Pos) {
    for ( int j = servo2PPos; j >= servo2Pos; j--) {   // Run servo down
      servo02.write(j);
      delay(10);    // defines the speed at which the servo rotates
    }
  }
  if (servo2PPos < servo2Pos) {
    for ( int j = servo2PPos; j <= servo2Pos; j++) {   // Run servo up
      servo02.write(j);
      delay(10);
    }
  }
  servo2PPos = servo2Pos;

  if (servo6PPos > servo6Pos) {
    for ( int j = servo6PPos; j >= servo6Pos; j--) {
      servo06.write(j);
      delay(10);
    }
  }
  if (servo6PPos < servo6Pos) {
    for ( int j = servo6PPos; j <= servo6Pos; j++) {
      servo06.write(j);
      delay(10);
    }
  }
  servo6PPos = servo6Pos;
}

void up(int e,int f,int g,int h){
   servo2Pos = e;
   servo3Pos = f;
   servo5Pos = g;
   servo6Pos = h;

  if (servo2PPos > servo2Pos) {
        for ( int j = servo2PPos; j >= servo2Pos; j--) {   // Run servo down
          servo02.write(j);
          delay(10);    // defines the speed at which the servo rotates
        }
      }
      // If previous position is smaller then current position
      if (servo2PPos < servo2Pos) {
        for ( int j = servo2PPos; j <= servo2Pos; j++) {   // Run servo up
          servo02.write(j);
          delay(10);
        }
      }
      servo2PPos = servo2Pos;

  if (servo3PPos > servo3Pos) {
        for ( int j = servo3PPos; j >= servo3Pos; j--) {
          servo03.write(j);
          delay(10);
        }
      }
      if (servo3PPos < servo3Pos) {
        for ( int j = servo3PPos; j <= servo3Pos; j++) {
          servo03.write(j);
          delay(10);
        }
      }
      servo3PPos = servo3Pos;
           
  if (servo5PPos > servo5Pos) {
        for ( int j = servo5PPos; j >= servo5Pos; j--) {
          servo05.write(j);
          delay(10);
        }
      }
      if (servo5PPos < servo5Pos) {
        for ( int j = servo5PPos; j <= servo5Pos; j++) {
          servo05.write(j);
          delay(10);
        }
      }
      servo5PPos = servo5Pos;

    if (servo6PPos > servo6Pos) {
        for ( int j = servo6PPos; j >= servo6Pos; j--) {
          servo06.write(j);
          delay(10);
        }
      }
      if (servo6PPos < servo6Pos) {
        for ( int j = servo6PPos; j <= servo6Pos; j++) {
          servo06.write(j);
          delay(10);
        }
      }
      servo6PPos = servo6Pos; 
     servo02.detach();
      servo03.detach();
      servo05.detach();
}
