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
