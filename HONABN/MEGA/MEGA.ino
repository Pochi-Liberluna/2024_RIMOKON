#include<PCA9685.h>
#include<Servo.h>

#include"./../Class/move.h"

Servo Servo1, Servo2, Servo3, Servo4;

void setup(){
  Serial.begin(115200);
  Servo1.attach();
  Servo2.attach();
  Servo3.attach();
  Servo4.attach();
}

void loop(){
  if(Serial.available() > 0){
    char ;
  }
}
