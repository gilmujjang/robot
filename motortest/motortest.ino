int left1 = 24;
int left2 = 23;
int leftspeed = 44;
int right1 = 28;
int right2 = 27;
int rightspeed = 45;

void setup() {
  digitalWrite(left1, LOW);
  digitalWrite(left2, LOW);
  analogWrite(leftspeed, 0);
  digitalWrite(right1, LOW);
  digitalWrite(right2, LOW);
  analogWrite(rightspeed, 0);
  Serial.begin(115200);
  Serial.print("Starting...\n");

}

void loop() {
  Serial.println("hi");
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  analogWrite(leftspeed, 100);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
  analogWrite(rightspeed, 100);

}
