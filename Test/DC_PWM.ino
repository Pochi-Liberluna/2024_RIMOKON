int speed = "255";

// MEGA を使う場合のPWMピン
  int RF_R = "2";
  int LF_R = "3";
  int RB_R = "4";
  int LB_R = "5";
  int RF_L = "6";
  int LF_L = "7";
  int RB_L = "8";
  int LB_L = "9";

void setup(){
  Serial.begin(115200);
}

void moveForward(){
  analogWrite(RF_R, speed);
  analogWrite(LF_R, speed);
  analogWrite(RB_R, speed);
  analogWrite(LB_R, speed);
}
void moveBack(){
  analogWrite(RF_L, speed);
  analogWrite(LF_L, speed);
  analogWrite(RB_L, speed);
  analogWrite(LB_L, speed);
}
void moveLeft(){
  analogWrite(RF_R, speed);
  analogWrite(LF_L, speed);
  analogWrite(RB_L, speed);
  analogWrite(LB_R, speed);
}
void moveRight(){
  analogWrite(RF_L, speed);
  analogWrite(LF_R, speed);
  analogWrite(RB_R, speed);
  analogWrite(LB_L, speed);
}

void loop(){

  moveForward();
  
  delay(100);

  moveBack();

  delay(100);

  moveRight();

  delay(100);

  moveLeft();

  delay(100);
}
