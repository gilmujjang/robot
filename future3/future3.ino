int left1 = 24;
int left2 = 23;
int leftspeed = 44;
int right1 = 27;
int right2 = 28;
int rightspeed = 45;
int q =0;
#include <PIDLoop.h>
#include <Pixy2.h>
#include <Servo.h>
#include <DFRobot_TFmini.h>

Servo servo02;
Servo servo03;
Servo servo05;
Servo servo06;
Pixy2 pixy;
int servo2Pos, servo3Pos, servo5Pos, servo6Pos; // current position
int servo2PPos, servo3PPos, servo5PPos, servo6PPos; // previous position
SoftwareSerial mySerial(11,10); // RX, TX

DFRobot_TFmini  TFmini;
uint16_t distance, strength;  // 거리와 강도를 담는 변수



void setup(){
  Serial.begin(115200);
  Serial.print("Starting...\n");
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
  TFmini.begin(mySerial);
  
}

void loop(){
  int i;
  int q=10;
  int s=100;
  Serial.println("loop excute");
  while(1){
    pixy.ccc.getBlocks();
    distance = TFmini.getDistance();
    delay(500);
    if (pixy.ccc.numBlocks){
      Serial.print("Detected ");
      Serial.println(pixy.ccc.numBlocks);
      for (i=0; i<pixy.ccc.numBlocks; i++){
        Serial.print("  block ");
        Serial.print(i);
        Serial.print(": ");
        pixy.ccc.blocks[i].print();
      }

      pixy.ccc.getBlocks();
      if(pixy.ccc.blocks[0].m_x < 130){
        Serial.print(pixy.ccc.blocks[0].m_x);
        Serial.println("좌회전");
        digitalWrite(left1, LOW);
        digitalWrite(left2, HIGH);
        analogWrite(leftspeed, s);
        digitalWrite(right1, HIGH);
        digitalWrite(right2, LOW);
        analogWrite(rightspeed, s);
        delay(q);
      }
      if(pixy.ccc.blocks[0].m_x > 160){
        Serial.print(pixy.ccc.blocks[0].m_x);
        Serial.println("우회전");
        digitalWrite(left1, HIGH);
        digitalWrite(left2, LOW);
        analogWrite(leftspeed, s);
        digitalWrite(right1, LOW);
        digitalWrite(right2, HIGH);
        analogWrite(rightspeed, s);
        delay(q);
      }
      if(130<pixy.ccc.blocks[0].m_x && pixy.ccc.blocks[0].m_x < 160){
        Serial.print(pixy.ccc.blocks[0].m_x);
        Serial.println("좌우 정렬 완료");
        digitalWrite(left1, LOW);
        digitalWrite(left2, LOW);
        analogWrite(leftspeed, 0);
        digitalWrite(right1, LOW);
        digitalWrite(right2, LOW);
        analogWrite(rightspeed, 0);
      }

      if(distance<14){
        Serial.print(distance);
        Serial.println("cm");
        Serial.println("너무 가까워서 후진");
        digitalWrite(left1, LOW);
        digitalWrite(left2, HIGH);
        analogWrite(leftspeed, s);
        digitalWrite(right1, LOW);
        digitalWrite(right2, HIGH);
        analogWrite(rightspeed, s);
      }
    
      if(distance>16){
        Serial.print(distance);
        Serial.println("cm");
        Serial.println("멀어서 전진");
        digitalWrite(left1, HIGH);
        digitalWrite(left2, LOW);
        analogWrite(leftspeed, s);
        digitalWrite(right1,HIGH);
        digitalWrite(right2, LOW);
        analogWrite(rightspeed, s);
        delay(q);
      }

      if(distance>16 && distance<14){
        Serial.print(distance);
        Serial.println("cm");
        Serial.println("적당한 거리라서 정지");
        digitalWrite(left1, LOW);
        digitalWrite(left2, LOW);
        analogWrite(leftspeed, 0);
        digitalWrite(right1, LOW);
        digitalWrite(right2, LOW);
        analogWrite(rightspeed, 0);
      }
      
      if(130<pixy.ccc.blocks[0].m_x && pixy.ccc.blocks[0].m_x<160 && distance>16 && distance<14){
        Serial.println("로봇 정위치");
        break;
      }
    }
  }
  delay(1000);
  Serial.println("로봇팔 시동");
  servo02.attach(5);
  servo03.attach(6);
  servo05.attach(8);
  servo06.attach(9);
  delay(20);
  servo2PPos = 180;
  servo02.write(servo2PPos);
  servo3PPos = 90;
  servo03.write(servo3PPos);
  servo5PPos = 100;
  servo05.write(servo5PPos);
  servo6PPos = 80;
  servo06.write(servo6PPos);
  delay(1000);
  Serial.println("로봇팔 잡기 시작");
  get(70,60,170,0);
  delay(1000);
  Serial.println("로봇팔 잡기 완료, 들기 시작");
  up(150,90,100);
  servo02.detach();
  servo03.detach();
  servo05.detach();
  Serial.println("로봇팔 들기 완료, 전원 차단");
  delay(500);
  Serial.println("로봇 180도 회전");
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  analogWrite(leftspeed, s);
  digitalWrite(right1,LOW);
  digitalWrite(right2, HIGH);
  analogWrite(rightspeed,300);
  Serial.println("로봇 회전 완료");
  
  
}

void get(int a,int b,int c,int d){
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

void up(int e,int f,int g)
{
  servo2Pos = e;
  servo3Pos = f;
  servo5Pos = g;

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

    servo02.detach();
    servo03.detach();
    servo05.detach();
}
