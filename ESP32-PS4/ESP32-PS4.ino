/*ESP32に記述*/
#include<ps4.h>
#include<PS4Controller.h>
// #include<SPI.h>

#include"../Class/move.h"

// #define

 /* PCA9685 pwm = PCA9685(0x40);
  move DC_Motor; */

void setup(){
  Serial.begin(9600);
  // Bluetooth MACアドレスの表示
  uint8_t bt_mac[6];
  esp_read_mac(bt_mac, ESP_MAC_BT);
  Serial.printf("Bluetooth Mac Address => %02X;%02X:%02X:%02X:%02X:%02X\r\n", bt_mac[0], bt_mac[1], bt_mac[2], bt_mac[3], bt_mac[4], bt_mac[5]);

  PS4.begin("1a:2b:3c:01:01:01"); //MACアドレス
  Serial.printf("Ready.");

 /* pwm.begin();
  pwm.setPWMFreq(50); //PWM周期を50Hzに設定 */

  // DC_Motor.speed = 100;
}

void loop(){
  
  int LJoyX = PS4.LStickX();
  int LJoyY = PS4.LStickY();
  int RJoyX = PS4.RStickX();
  int RJoyY = PS4.RStickY();
  
  if(PS4.isConnected()){

    Serial.printf("Connected.\n");
    //Serial.printf("Battery Level : %d\n", PS4.Battery());

    if(PS4.Right()) Serial.write('a');
    if(PS4.Left()) Serial.write('b');
    if(PS4.Up()) Serial.write('c');
    if(PS4.Down()) Serial.write('d');

    if(PS4.Square()) Serial.write('e'); //□
    if(PS4.Cross()) Serial.write('f'); //×
    if(PS4.Circle()) Serial.write('g'); //○
    if(PS4.Triangle()) Serial.write('h'); //△

    if(PS4.UpRight()) Serial.write('i');
    if(PS4.DownRight()) Serial.write('j');
    if(PS4.UpLeft()) Serial.write('k');
    if(PS4.DownLeft()) Serial.write('l');

    if(PS4.L1()) Serial.write('m');
    if(PS4.R1()) Serial.write('n');

    if(PS4.Share()) Serial.write('o');
    if(PS4.Options()) Serial.write('p');
    if(PS4.L3()) Serial. write('q');
    if(PS4.R3()) Serial.write('r');

    if(PS4.PSButton()) Serial.write('s');
    if(PS4.Touchpad()) Serial.write('t');

  /*  if(PS4.L2()){
       Serial.printf("L2 button at %d\n", PS4.L2Value());
      }
      if(PS4.R2()){
        Serial.printf("R2 button at %d\n", PS4.R2Value());
      }
      if(PS4.LStickX()){
        Serial.printf("Left Stick X at %d\n", PS4.LStickX());
      }
      if(PS4.LStickY()){
        Serial.printf("Left Stick Y at %d\n", PS4.LStickY());
      }
      if(PS4.RStickX()){
        Serial.printf("Right Stick X at %d\n", PS4.RStickX());
      }
      if(PS4.RStickY()){
        Serial.printf("Righr Stick Y at %d\n", PS4.RStickY());
      }  */

      Serial.println();
      // delay(10);
  }
  if(LJoyY >= 175){
   // DC_Mortor.moveForward();
   Serial.write('0');
  }
  if(LJoyY =< 75){
   // DC_Motor.moveBack();
   Serial.write('1');
  }
}
