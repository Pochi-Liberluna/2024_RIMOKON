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
  analogWrigte(RF_R, speed);
  analogWrigte(LF_R, speed);
  analogWrigte(RB_R, speed);
  analogWrigte(LB_R, speed);
}
void moveBack(){
  analogWrigte(RF_L, speed);
  analogWrigte(LF_L, speed);
  analogWrigte(RB_L, speed);
  analogWrigte(LB_L, speed);
}
void moveLeft(){
  analogWrigte(RF_R, speed);
  analogWrigte(LF_L, speed);
  analogWrigte(RB_L, speed);
  analogWrigte(LB_R, speed);
}
void moveRight(){
  analogWrigte(RF_L, speed);
  analogWrigte(LF_R, speed);
  analogWrigte(RB_R, speed);
  analogWrigte(LB_L, speed);
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
