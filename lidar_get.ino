#include <DFRobot_TFmini.h>
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial mySerial(11, 10); // RX, TX
DFRobot_TFmini TFmini;
uint16_t distance;

Servo servo02;
Servo servo03;
Servo servo05;
Servo servo06;

int servo2Pos, servo3Pos, servo5Pos, servo6Pos; // current position
int servo2PPos, servo3PPos, servo5PPos, servo6PPos; // previous position

int left1 = 23;
int left2 = 24;
int leftspeed = 44;
int right1 = 28;
int right2 = 27;
int rightspeed = 45;

int speedDelay = 20;
int index = 0;
String dataIn = "";


void setup() 
{
  pinMode(left1,OUTPUT);
  pinMode(left2,OUTPUT);
  //pinMode(leftspeed,OUTPUT);
  pinMode(right1,OUTPUT);
  pinMode(right2,OUTPUT);
  //pinMode(rightspeed,OUTPUT);

  digitalWrite(left1, LOW);
  digitalWrite(left2, LOW);
  analogWrite(leftspeed, 0);
  digitalWrite(right1, LOW);
  digitalWrite(right2, LOW);
  analogWrite(rightspeed, 0);
  
  Serial.begin(115200);
  TFmini.begin(mySerial);
  servo02.attach(5);
  servo03.attach(6);
  servo05.attach(8);
  servo06.attach(9);
  delay(20);
  servo2PPos = 170;
  servo02.write(servo2PPos);
  servo3PPos = 90;
  servo03.write(servo3PPos);
  servo5PPos = 100;
  servo05.write(servo5PPos);
  servo6PPos = 80;
  servo06.write(servo6PPos);
  
  Serial.println("시작");
}


void loop()
{
  delay(1000);
  servo02.detach();
  servo03.detach();
  servo05.detach();
  servo06.detach();
  
  while(1)
  {
    if(TFmini.measure())
    {
        distance = TFmini.getDistance();       //Get distance data
        Serial.print("Distance = ");
        Serial.println(distance);
        delay(10);
        digitalWrite(left1, LOW);
        digitalWrite(left2, HIGH);
        analogWrite(leftspeed, 150);
        digitalWrite(right1, LOW);
        digitalWrite(right2, HIGH);
        analogWrite(rightspeed, 150);
        
        if(distance==20)
        {
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
        else if(distance<20)
        {
          digitalWrite(left1, LOW);
          digitalWrite(left2, HIGH);
          analogWrite(leftspeed, 150);
          digitalWrite(right1, LOW);
          digitalWrite(right2, HIGH);
          analogWrite(rightspeed, 150);
        }
    }                
   }
   up(150,90,100,10);
   delay(1000);
    
}


void get(int a,int b,int c,int d)
{
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
      // If previous position is smaller then current position
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

void up(int e,int f,int g,int h)
{
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
     
}
