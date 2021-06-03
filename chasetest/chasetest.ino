#include <PIDLoop.h>
#include <Pixy2.h>

#define MAX_TRANSLATE_VELOCITY  200

Pixy2 pixy;
int left1 = 24;
int left2 = 23;
int leftspeed = 44;
int right1 = 27;
int right2 = 28;
int rightspeed = 45;

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
}

void loop(){
  int i;
  digitalWrite(left1, LOW);
  digitalWrite(left2, LOW);
  analogWrite(leftspeed, 0);
  digitalWrite(right1, LOW);
  digitalWrite(right2, LOW);
  analogWrite(rightspeed, 0);
  pixy.ccc.getBlocks();
  Serial.println("loop excute");
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
      Serial.println("left");
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
      Serial.println("right");
      digitalWrite(left1, HIGH);
      digitalWrite(left2, LOW);
      analogWrite(leftspeed, 120);
      digitalWrite(right1, LOW);
      digitalWrite(right2, HIGH);
      analogWrite(rightspeed, 120);
      delay(100);
    }
//    라이다로 쟀을떄 멀면 전진
  }  
}
