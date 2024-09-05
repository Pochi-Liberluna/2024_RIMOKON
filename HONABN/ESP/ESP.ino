#include <PS4Controller.h>

// ボタンの状態記録用
bool prevRight = false;
bool prevLeft = false;
bool prevUp = false;
bool prevDown = false;
bool prevSquare = false;
bool prevCross = false;
bool prevCircle = false;
bool prevTriangle = false;
bool prevUpRight = false;
bool prevDownRight = false;
bool prevUpLeft = false;
bool prevDownLeft = false;
bool prevL1 = false;
bool prevR1 = false;
bool prevShare = false;
bool prevOptions = false;
bool prevL3 = false;
bool prevR3 = false;
bool prevPSButton = false;
bool prevTouchpad = false;



void setup() {
  Serial.begin(115200);
  PS4.begin("1a:2b:3c:00:11:22");
  Serial.println("Ready.");
}

void loop() {
  
  int LJoyX = PS4.LStickX();
  int LJoyY = PS4.LStickY();
  int RJoyX = PS4.RStickX();
  int RJoyY = PS4.RStickY();


  if (PS4.isConnected()) {
    // ボタンの状態を取得
    bool RightPressed = PS4.Right();
    bool LeftPressed = PS4.Left();
    bool UpPressed = PS4.Up();
    bool DownPressed = PS4.Down();
    bool squarePressed = PS4.Square();
    bool crossPressed = PS4.Cross();
    bool circlePressed = PS4.Circle();
    bool trianglePressed = PS4.Triangle();
    bool UpRightPressed = PS4.UpRight();
    bool DownRightPressed = PS4.DownRight();
    bool UpLeftPressed = PS4.UpLeft();
    bool DownLeftPressed = PS4.DownLeft();
    bool L1Pressed = PS4.L1();
    bool R1Pressed = PS4.R1();
    bool SharePressed = PS4.Share();
    bool OptionsPressed = PS4.Options();
    bool L3Pressed = PS4.L3();
    bool R3Pressed = PS4.R3();
    bool PSButtonPressed = PS4.PSButton();
    bool TouchpadPressed = PS4.Touchpad();

    if (RightPressed != prevRight) {
      if (RightPressed) {
        Serial.write('a');  
      }
    }


    if (LeftPressed != prevLeft) {
      if (LeftPressed) {
        Serial.write('b');  
      }
    }


    if (UpPressed != prevUp) {
      if (UpPressed) {
        Serial.write('c');  
      }
    }


    if (DownPressed != prevDown) {
      if (DownPressed) {
        Serial.write('d');  
      }
    }

    if (squarePressed != prevSquare) {
      if (squarePressed) {
        Serial.write('e');  
      }
    }


    if (crossPressed != prevCross) {
      if (crossPressed) {
        Serial.write('f');  
      }
    }


    if (circlePressed != prevCircle) {
      if (circlePressed) {
        Serial.write('g');  
      }
    }


    if (trianglePressed != prevTriangle) {
      if (trianglePressed) {
        Serial.write('h');  
      }
    }


    if (UpRightPressed != prevUpRight) {
      if (UpRightPressed) {
        Serial.write('i');  
      }
    }


    if (DownRightPressed != prevDownRight) {
      if (DownRightPressed) {
        Serial.write('j');  
      }
    }


    if (UpLeftPressed != prevUpLeft) {
      if (UpLeftPressed) {
        Serial.write('k');  
      }
    }

    if (DownLeftPressed != prevDownLeft) {
      if (DownLeftPressed) {
        Serial.write('l');  
      }
    }

    if (L1Pressed != prevL1) {
      if (L1Pressed) {
        Serial.write('m');  
      }
    }

    if (R1Pressed != prevR1) {
      if (R1Pressed) {
        Serial.write('n');  
      }
    }

    // if (L2Pressed != prevL2) {
    //   if (L2Pressed) {
    //     Serial.write('o');  
    //   }
    // }

    //   if (R2Pressed != prevR2) {
    //   if R2(Pressed) {
    //     Serial.write('p');  
    //   }
    // }

    if (SharePressed != prevShare) {
      if (SharePressed) {
        Serial.write('q');  
      }
    }

    if (OptionsPressed != prevOptions) {
      if (OptionsPressed) {
        Serial.write('r');  
      }
    }

    if (L3Pressed != prevL3) {
      if (L3Pressed) {
        Serial.write('s');  
      }
    }

    if (R3Pressed != prevR3) {
      if (R3Pressed) {
        Serial.write('t');  
      }
    }

    if (PSButtonPressed != prevPSButton) {
      if (PSButtonPressed) {
        Serial.write('u');  
      }
    }

    if (TouchpadPressed != prevTouchpad) {
      if (TouchpadPressed) {
        Serial.write('v');  
      }
    }

    if(PS4.L2()){
       Serial.printf("\nL2 button at %d\n", PS4.L2Value());
    }

    if(PS4.R2()){
        Serial.printf("\nR2 button at %d\n", PS4.R2Value());
    }
    
    if(PS4.LStickX()){
        Serial.printf("\nLeft Stick X at %d\n", PS4.LStickX());
    }

    if(PS4.LStickY()){
        Serial.printf("\nLeft Stick Y at %d\n", PS4.LStickY());
    }

    if(PS4.RStickX()){
        Serial.printf("\nRight Stick X at %d\n", PS4.RStickX());
    }
    
    if(PS4.RStickY()){
        Serial.printf("\nRight Stick Y at %d\n", PS4.RStickY());
    }


    // 前の状態を更新
    prevRight = RightPressed;
    prevLeft = LeftPressed;
    prevUp = UpPressed;
    prevDown = DownPressed;
    prevSquare = squarePressed;
    prevCross = crossPressed;
    prevCircle = circlePressed;
    prevTriangle = trianglePressed;
    prevUpRight = UpRightPressed;
    prevUpLeft = UpLeftPressed;
    prevDownRight = DownRightPressed;
    prevDownLeft = DownLeftPressed;
    prevL1 = L1Pressed;
    prevR1 = R1Pressed;
    prevShare = SharePressed;
    prevOptions = OptionsPressed;
    prevL3 = L3Pressed;
    prevR3 = R3Pressed;
    prevPSButton = PSButtonPressed;
    prevTouchpad = TouchpadPressed;
    
    delay(100);
  }
}
