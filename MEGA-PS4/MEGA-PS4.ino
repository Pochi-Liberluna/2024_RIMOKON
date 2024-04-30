/** Serial.read()用
a = PS4.Right();  b = PS4.Left();  c = PS4.Up();  d = PS4.Down();
e = PS4.Square();  f = PS4.Cross();  g = PS4.Circle();  h = PS4.Triangle();
i = PS4.UpRight();  j = PS4.DownRight();  k = PS4.UpLeft();  l = PS4.DownLeft();
m = PS4.L1();  n = PS4.R1();  o = PS4.L2();  p = PS4.R2();
q = PS4.Share();  r = PS4.Options();  s = PS4.L3();  t = PS4.R3();
u = PS4.PSButton();  v = PS4.Touchpad();
0 = moveForward();  1 = moveBack();  2 = moveRight();  3 = moveLeft();
**/
#include"../../ESP32-PS4/Class/move.h"

#include<PCA9685.h>
#include<BTS7960.h>
#include<SoftwareSerial.h>
#include<SPI.h>
#include<Adafruit_PWMServoDriver.h>

#define SERVO_MIN 130 
#define SERVO_MAX 500

move DC_Motor;
//PCA9685 pwm = PCA9685(0x40);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setAngle(uint8_t ch, int angle){
  long val;

  val = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  pwm.setPWM(ch, 0, val);
}

void setup(){
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(50); //PWM周期を50Hzに設定

}
void loop(){
  if(Serial.available() > 0){
    char rChar = Serial.read();

    if(rChar == 'a'){
      
    }
    if(rChar == 'b'){
      
    }
    if(rChar == 'c'){
      
    }
    if(rChar == 'd'){
      
    }
    if(rChar == 'e'){
      
    }
    if(rChar == 'f'){
      
    }
    if(rChar == 'g'){
      
    }
    if(rChar == 'h'){
      
    }
    if(rChar == 'i'){
      
    }
    if(rChar == 'j'){
      
    }
    if(rChar == 'k'){
      
    }
    if(rChar == 'l'){
      
    }
    if(rChar == 'm'){
      
    }
    if(rChar == 'n'){
      
    }
    if(rChar == 'o'){
      
    }
    if(rChar == 'p'){
      
    }
    if(rChar == 'q'){
      
    }
    if(rChar == 's'){
      
    }
    if(rChar == 't'){
      
    }
    if(rChar == 'u'){
      
    }
    if(rChar == 'v'){
      
    }
    if(rChar == '0'){
      DC_Motor.moveForward();
    }
    if(rChar == '1'){
      DC_Motor.moveBack();
    }
    if(rChar == '2'){
      
    }
    if(rChar == '3'){
      
    }
  }
}
