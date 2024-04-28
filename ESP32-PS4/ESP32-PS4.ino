/*ESP32に記述*/
#include<ps4.h>
#include<PS4Controller.h>

#include"../Class/move.h"

// #define

  move DC_Motor;

void setup(){
  Serial.begin(9600);
  // Bluetooth MACアドレスの表示
  uint8_t bt_mac[6];
  esp_read_mac(bt_mac, ESP_MAC_BT);
  Serial.printf("Bluetooth Mac Address => %02X;%02X:%02X:%02X:%02X:%02X\r\n", bt_mac[0], bt_mac[1], bt_mac[2], bt_mac[3], bt_mac[4], bt_mac[5]);

  PS4.begin("1a:2b:3c:01:01:01"); //MACアドレス
  Serial.printf("Ready.");

  // DC_Motor.speed = 100;
}

void loop(){
  if(PS4.isConnected()){

    Serial.printf("Connected.\n");
    //Serial.printf("Battery Level : %d\n", PS4.Battery());

    if(PS4.Right()) Serial.println("Right Button\n");
    if(PS4.Left()) Serial.println("Left Button\n");
    if(PS4.Up()) Serial.println("Up Button\n");
    if(PS4.Down()) Serial.println("Down Button\n");

    if(PS4.Square()) Serial.println("Square Button\n"); //□
    if(PS4.Cross()) Serial.println("Cross Button\n"); //×
    if(PS4.Circle()) Serial.println("Circle Button\n"); //○
    if(PS4.Triangle()) Serial.println("Triangle Button\n"); //△

    if(PS4.UpRight()) Serial.println("UpRight Button\n");
    if(PS4.DownRight()) Serial.println("DownRight Button\n");
    if(PS4.UpLeft()) Serial.println("UpLeft Button\n");
    if(PS4.DownLeft()) Serial.println("DownLeft Button\n");

    if(PS4.L1()) Serial.println("L1 Button\n");
    if(PS4.R1()) Serial.println("R1 Button\n");

    if(PS4.Share()) Serial.println("Share Button\n");
    if(PS4.Options()) Serial.println("Options Button\n");
    if(PS4.L3()) Serial.println("L3 Button\n");
    if(PS4.R3()) Serial.println("R3 Button\n");

    if(PS4.PSButton()) Serial.println("PS Button\n");
    if(PS4.Touchpad()) Serial.println("Touch Pad\n");

      if(PS4.L2()){
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
      }

      Serial.println();
      // delay(10);
  }

  void moveForward(){
    int LJoyStickX = PS4.LStickX();

    if(LJoyStickX >= 200){
      
    }
  }

}
