#include <PS4Controller.h>


void setup() {
  Serial.begin(115200);
  PS4.begin("1a:2b:c3:d4:5e");
  Serial.println("Ready.");


}


void loop(){
  
  int LJoyX = PS4.LStickX();
  int LJoyY = PS4.LStickY();
  int RJoyX = PS4.RStickX();
  int RJoyY = PS4.RStickY();
  
  if(PS4.isConnected()){

    // Serial.printf("Connected.\n");
    // //Serial.printf("Battery Level : %d\n", PS4.Battery());

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
    if(PS4.L2()) Serial.write('o');
    if(PS4.R2()) Serial.write('p');

    if(PS4.Share()) Serial.write('q');
    if(PS4.Options()) Serial.write('r');
    if(PS4.L3()) Serial. write('s');
    if(PS4.R3()) Serial.write('t');

    if(PS4.PSButton()) Serial.write('u');
    if(PS4.Touchpad()) Serial.write('v');

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
     // moveForward();
     // moveBack();
     // moveRight();
     // moveLeft();
  }
  // if(LJoyY >= 175){
  //  // DC_Mortor.moveForward();
  //  Serial.write('0');
  // }
  // if(LJoyY <= 75){
  //  // DC_Motor.moveBack();
  //  Serial.write('1');
  // }
}
