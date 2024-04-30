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

move DC_Motor;
PCA9685 pwm = PCA9685(0x40);

void setup(){
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(50); //PWM周期を50Hzに設定

}
void loop(){
  if(Serial.available() > 0){
    char rChar = Serial.read();

    if(rChar == 'a'){
      //関数を実装し実行させる。
    }
    //省略
    if(rChar == '0'){
      DC_Motor.moveForward();
    }
    if(rChar == '1'){
      DC_Motor.moveBack();
    }
  }
}
