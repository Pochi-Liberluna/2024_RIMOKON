/*
 Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PCA9685.h>            //PCA9685用ヘッダーファイル（秋月電子通商作成）
PCA9685 pwm = PCA9685(0x40);    //PCA9685のアドレス指定（アドレスジャンパ未接続時）
PCA9685 pwm2 = PCA9685(0x41);   //PCA9685のアドレス指定（A0接続時）
#define SERVOMIN 0            //最小パルス幅 (標準的なサーボパルスに設定)
#define SERVOMAX 1200            //変更　最大パルス幅 (標準的なサーボパルス(600)に設定)

#include <PS3USB.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#include <MsTimer2.h>
#include <TimerOne.h>
#include <avr/interrupt.h>

USB Usb;
/* You can create the instance of the class in two ways */
PS3USB PS3(&Usb); // This will just create the instance
//PS3USB PS3(&Usb,0x00,0x15,0x83,0x3D,0x0A,0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printAngle;
uint8_t state = 0;

//-------------------------------------------
//定数の設定
#define w11 62   // ﾓｰﾀｰ1用_正転 / ボタン△ / TRIANGLE
#define w12 63  // ﾓｰﾀｰ1用_逆転 / ボタン× / CROSS------[PWM]
#define w13 64  // ﾓｰﾀｰ2用_正転 / ボタン○ / CIRCLE
#define w14 65  // ﾓｰﾀｰ2用_逆転 / ボタン□ / SQUARE------[PWM]
#define w15 66  // ﾓｰﾀｰ3用_正転 / 十字ｷｰ_上  / UP----------[PWM]
#define w16 67  // ﾓｰﾀｰ3用_逆転 / 十字ｷｰ_下  / DOWN
#define w17 68  // ﾓｰﾀｰ4用_正転 / 十字ｷｰ_右  / RIGHT
#define w18 69  // ﾓｰﾀｰ4用_逆転 / 十字ｷｰ_左  / LEFT--------[PWM]
#define w21 22   // ﾓｰﾀｰ5用_正転 / ｽﾃｨｯｸ左_前 / LeftHatY_Front
#define w22 23  // ﾓｰﾀｰ5用_逆転 / ｽﾃｨｯｸ左_後 / LeftHatY_Back
#define w23 24  // ﾓｰﾀｰ6用_正転 / ｽﾃｨｯｸ右_前 / RightHatY_Front
#define w24 25// ﾓｰﾀｰ6用_逆転 / ｽﾃｨｯｸ右_後 / RightHatY_Back
#define w25 26
#define w26 27
#define w27 28
#define w28 29
#define w31 30
#define w32 31
#define w33 32
#define w34 33 
#define w35 34
#define w36 35
#define w37 36
#define w38 37
#define w41 38
#define w42 39
#define w43 40
#define w44 41
#define w45 42
#define w46 43
#define w47 44
#define w48 45
#define w51 46
#define w52 47 
#define w53 48
#define w54 49
#define w55 50 
#define w56 51
#define w57 52
#define w58 53
#define p01 54
#define p02 55
#define p03 56
#define p04 57
#define p05 58
#define p06 59
#define p07 60
#define p08 61
#define p11 2
#define p12 3
#define p13 4
#define p14 5
#define p15 6
#define p16 7
#define p17 8
#define p18 9
#define r1  14
#define r2  15
#define r3  16
#define r4  17
#define r5  18
#define r6  19

#define a 50      //ｻｰﾎﾞﾓｰﾀ角度１
#define b 65     //ｻｰﾎﾞﾓｰﾀ角度２
#define c 80     //ｻｰﾎﾞﾓｰﾀ角度３
#define d 95    //ｻｰﾎﾞﾓｰﾀ角度４
#define e 210    //ｻｰﾎﾞﾓｰﾀ角度５

#define f 300   //自立モード(ﾀｯﾁﾀﾞｳﾝ)スピード
#define g 500   //自立モードスピード
#define h 500   //操作モードスピード
#define i 250   //操作モードスピードslow
#define j 1000   //操作モードスピードfast
#define k 0

int aa=0; int bb=0; int cc; int dd=HIGH; int ee=HIGH; int ff=HIGH; int gg=HIGH; int hh=0; int ii=0;
int jj=HIGH; int kk=HIGH; int ll=HIGH; int mm=HIGH; int nn=HIGH; int oo=HIGH; int pp=HIGH; int qq=HIGH;
//I2C PWMボード制御用関数---------------------------------------------------------------------
void servo_write(int ch, int ang){ //動かすサーボチャンネルと角度を指定
  ang = map(ang, 0, 360, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（150～600）に変換
  pwm.setPWM(ch, 0, ang);
}
//--------------------------------------------------------------------------------------------




void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 USB Library Started"));


//I2C PWMボード初期設定(180°開)---------------------------------------------------
  pwm.begin();                   //初期設定 (アドレス0x40用)
  pwm.setPWMFreq(60);            //PWM周期を60Hzに設定 (アドレス0x40用)
  servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,k);
  servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,k);
  servo_write(8,190);servo_write(9,c);servo_write(10,c);servo_write(11,c);
  servo_write(12,c);servo_write(13,c);servo_write(14,c);servo_write(15,c);

//出力ピン初期設定-------------------------------------------------------
  pinMode(w11, OUTPUT);     //Arduinoのr1(2番)ピンを出力用として設定
  pinMode(w12, OUTPUT);     //Arduinoのr2(3番)ピンを出力用として設定
  pinMode(w13, OUTPUT);     //Arduinoのr3(4番)ピンを出力用として設定
  pinMode(w14, OUTPUT);     //Arduinoのr4(5番)ピンを出力用として設定
  pinMode(w15, OUTPUT);     //Arduinoのr5(6番)ピンを出力用として設定
  pinMode(w16, OUTPUT);     //Arduinoのr6(7番)ピンを出力用として設定
  pinMode(w17, OUTPUT);     //Arduinoのr7(8番)ピンを出力用として設定
  pinMode(w18, OUTPUT);     //Arduinoのr8(9番)ピンを出力用として設定
  pinMode(w21, OUTPUT);     //Arduinoのr9(14番)ピンを出力用として設定
  pinMode(w22, OUTPUT);    //Arduinoのr10(15番)ピンを出力用として設定
  pinMode(w23, OUTPUT);    //Arduinoのr11(16番)ピンを出力用として設定
  pinMode(w24, OUTPUT);    //Arduinoのr12(17番)ピンを出力用として設定
  pinMode(w25, OUTPUT);
  pinMode(w26, OUTPUT);
  pinMode(w27, OUTPUT);
  pinMode(w28, OUTPUT);
  pinMode(w31, OUTPUT);
  pinMode(w32, OUTPUT);
  pinMode(w33, OUTPUT);
  pinMode(w34, OUTPUT);
  pinMode(w35, OUTPUT);
  pinMode(w36, OUTPUT);
  pinMode(w37, OUTPUT);
  pinMode(w38, OUTPUT);
  pinMode(w41, INPUT);
  pinMode(w42, INPUT);
  pinMode(w43, INPUT);
  pinMode(w44, INPUT);
  pinMode(w45, INPUT);
  pinMode(w46, INPUT);
  pinMode(w47, INPUT);
  pinMode(w48, INPUT);
  pinMode(w51, INPUT);
  pinMode(w52, INPUT);
  /*pinMode(w53, INPUT);
  pinMode(w54, INPUT);
  pinMode(w55, INPUT);
  pinMode(w56, INPUT);
  pinMode(w57, INPUT);
  pinMode(w58, INPUT);
  pinMode(p01, OUTPUT);
  pinMode(p02, OUTPUT);
  pinMode(p03, OUTPUT);
  pinMode(p04, OUTPUT);
  pinMode(p05, OUTPUT);
  pinMode(p06, OUTPUT);
  pinMode(p07, OUTPUT);
  pinMode(p08, OUTPUT);
  pinMode(p11, OUTPUT);
  pinMode(p12, OUTPUT);
  pinMode(p13, OUTPUT);
  pinMode(p14, OUTPUT);
  pinMode(p15, OUTPUT);
  pinMode(p16, OUTPUT);
  pinMode(p17, OUTPUT);
  pinMode(p18, OUTPUT);
  pinMode(r1, INPUT);
  pinMode(r2, INPUT);
  pinMode(r3, INPUT);
  pinMode(r4, INPUT);
  pinMode(r5, INPUT);
  pinMode(r6, INPUT);*/

  digitalWrite(w11,HIGH);    //r1の初期値をHIGHに設定
  digitalWrite(w12,HIGH);    //r2の初期値をHIGHに設定
  digitalWrite(w13,HIGH);    //r3の初期値をHIGHに設定
  digitalWrite(w14,HIGH);    //r4の初期値をHIGHに設定
  digitalWrite(w15,HIGH);    //r5の初期値をHIGHに設定
  digitalWrite(w16,HIGH);    //r6の初期値をHIGHに設定
  digitalWrite(w17,HIGH);    //r7の初期値をHIGHに設定
  digitalWrite(w18,HIGH);    //r8の初期値をHIGHに設定
  digitalWrite(w21,HIGH);    //r9の初期値をHIGHに設定
  digitalWrite(w22,HIGH);   //r10の初期値をHIGHに設定
  digitalWrite(w23,HIGH);   //r11の初期値をHIGHに設定
  digitalWrite(w24,HIGH);   //r12の初期値をHIGHに設定
  digitalWrite(w25,HIGH);
  digitalWrite(w26,HIGH);
  digitalWrite(w27,HIGH);
  digitalWrite(w28,HIGH);
  digitalWrite(w31,HIGH);
  digitalWrite(w32,HIGH);
  digitalWrite(w33,HIGH);
  digitalWrite(w34,HIGH);
  digitalWrite(w35,HIGH);
  digitalWrite(w36,HIGH);
  digitalWrite(w37,HIGH);
  digitalWrite(w38,HIGH);
  /*digitalWrite(w41,HIGH);
  digitalWrite(w42,HIGH);
  digitalWrite(w43,HIGH);
  digitalWrite(w44,HIGH);
  digitalWrite(w45,HIGH);
  digitalWrite(w46,HIGH);
  digitalWrite(w47,HIGH);
  digitalWrite(w48,HIGH);
  digitalWrite(w51,HIGH);
  digitalWrite(w52,HIGH);
  digitalWrite(w53,HIGH);
  digitalWrite(w54,HIGH);
  digitalWrite(w55,HIGH);
  digitalWrite(w56,HIGH);
  digitalWrite(w57,HIGH);
  digitalWrite(w58,HIGH);
  digitalWrite(p01,HIGH);
  digitalWrite(p02,HIGH);
  digitalWrite(p03,HIGH);
  digitalWrite(p04,HIGH);
  digitalWrite(p05,HIGH);
  digitalWrite(p06,HIGH);
  digitalWrite(p07,HIGH);
  digitalWrite(p08,HIGH);
  digitalWrite(p11,HIGH);
  digitalWrite(p12,HIGH);
  digitalWrite(p13,HIGH);
  digitalWrite(p14,HIGH);
  digitalWrite(p15,HIGH);
  digitalWrite(p16,HIGH);
  digitalWrite(p17,HIGH);
  digitalWrite(p18,HIGH);
  digitalWrite(r1,HIGH);
  digitalWrite(r2,HIGH);
  digitalWrite(r3,HIGH);
  digitalWrite(r4,HIGH);
  digitalWrite(r5,HIGH);
  digitalWrite(r6,HIGH);*/

  aa=0;bb=0;cc=h;


}

//******************************************************************************/
volatile void delay_ms(unsigned long unit)
{
  do {
    delay(1);if(PS3.getButtonClick(PS)){asm volatile ("  jmp 0");}
  } while(--unit != 0);
}
//******************************************************************************/
//プログラムリセット処理----------------------------------------------------
volatile void software_reset() {
  asm volatile ("  jmp 0");
  } 
//----------------------------------------------------------------------


void loop() {
  Usb.Task();

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS3.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      if (PS3.PS3Connected) { // The Navigation controller only have one joystick
        Serial.print(F("\tRightHatX: "));
        Serial.print(PS3.getAnalogHat(RightHatX));
        Serial.print(F("\tRightHatY: "));
        Serial.print(PS3.getAnalogHat(RightHatY));
      }
    }

//ジョイスティックの制御------------------------------------------------------

      if ((PS3.getAnalogHat(LeftHatY) == 0)&&(PS3.getAnalogHat(LeftHatX) == 127)&&(PS3.getAnalogHat(RightHatY) == 0)&&(PS3.getAnalogHat(RightHatX) == 127))
      {servo_write(0,cc);servo_write(1,k);servo_write(2,cc);servo_write(3,k);servo_write(4,cc);servo_write(5,k);servo_write(6,cc);servo_write(7,k);}//正転
      
      if ((PS3.getAnalogHat(LeftHatY) == 255)&&(PS3.getAnalogHat(LeftHatX) == 127)&&(PS3.getAnalogHat(RightHatY) == 255)&&(PS3.getAnalogHat(RightHatX) == 127))
      {servo_write(0,k);servo_write(1,cc);servo_write(2,k);servo_write(3,cc);servo_write(4,k);servo_write(5,cc);servo_write(6,k);servo_write(7,cc);}//逆転
      
      if ((PS3.getAnalogHat(LeftHatY) == 0)&&(PS3.getAnalogHat(LeftHatX) == 127)&&(PS3.getAnalogHat(RightHatY) == 255)&&(PS3.getAnalogHat(RightHatX) == 127))
      {servo_write(0,cc);servo_write(1,k);servo_write(2,cc);servo_write(3,k);servo_write(4,k);servo_write(5,cc);servo_write(6,k);servo_write(7,cc);}//右回転
     
      if ((PS3.getAnalogHat(LeftHatY) == 255)&&(PS3.getAnalogHat(LeftHatX) == 127)&&(PS3.getAnalogHat(RightHatY) == 0)&&(PS3.getAnalogHat(RightHatX) == 127))
      {servo_write(0,k);servo_write(1,cc);servo_write(2,k);servo_write(3,cc);servo_write(4,cc);servo_write(5,k);servo_write(6,cc);servo_write(7,k);}//左回転
      
      if ((PS3.getAnalogHat(LeftHatY) == 127)&&(PS3.getAnalogHat(LeftHatX) == 0)&&(PS3.getAnalogHat(RightHatY) == 127)&&(PS3.getAnalogHat(RightHatX) == 127))
      {servo_write(0,k);servo_write(1,cc);servo_write(2,cc);servo_write(3,k);servo_write(4,cc);servo_write(5,k);servo_write(6,k);servo_write(7,cc);}//左移動
      
      if ((PS3.getAnalogHat(LeftHatY) == 127)&&(PS3.getAnalogHat(LeftHatX) == 127)&&(PS3.getAnalogHat(RightHatY) == 127)&&(PS3.getAnalogHat(RightHatX) == 255))
      {servo_write(0,cc);servo_write(1,k);servo_write(2,k);servo_write(3,cc);servo_write(4,k);servo_write(5,cc);servo_write(6,cc);servo_write(7,k);}//右移動
      
      if ((PS3.getAnalogHat(LeftHatY) < 70)&&(PS3.getAnalogHat(LeftHatX) < 70)&&(PS3.getAnalogHat(RightHatY) == 127)&&(PS3.getAnalogHat(RightHatX) == 127))
      {servo_write(0,k);servo_write(1,k);servo_write(2,cc);servo_write(3,k);servo_write(4,cc);servo_write(5,k);servo_write(6,k);servo_write(7,k);}//斜め左上
      
      if ((PS3.getAnalogHat(LeftHatY) > 200)&&(PS3.getAnalogHat(LeftHatX) < 70)&&(PS3.getAnalogHat(RightHatY) == 127)&&(PS3.getAnalogHat(RightHatX) == 127))
      {servo_write(0,k);servo_write(1,cc);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,cc);}//斜め左下
      
      if ((PS3.getAnalogHat(LeftHatY) == 127)&&(PS3.getAnalogHat(LeftHatX) == 127)&&(PS3.getAnalogHat(RightHatY) < 70)&&(PS3.getAnalogHat(RightHatX) > 200))                                                              
      {servo_write(0,cc);servo_write(1,k);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,cc);servo_write(7,k);}//斜め右上
      
      if ((PS3.getAnalogHat(LeftHatY) == 127)&&(PS3.getAnalogHat(LeftHatX) == 127)&&(PS3.getAnalogHat(RightHatY) > 200)&&(PS3.getAnalogHat(RightHatX) > 200))
      {servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,cc);servo_write(4,k);servo_write(5,cc);servo_write(6,k);servo_write(7,k);}//斜め右下

      if ((PS3.getAnalogHat(LeftHatY) == 127)&&(PS3.getAnalogHat(LeftHatX) == 127)&&(PS3.getAnalogHat(RightHatY) == 127)&&(PS3.getAnalogHat(RightHatX) == 127))
      {servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,k);}//ブレーキ
      
      if ((PS3.getAnalogHat(LeftHatY) > 70)&&(PS3.getAnalogHat(LeftHatY) < 127)&&(PS3.getAnalogHat(RightHatY) > 70)&&(PS3.getAnalogHat(RightHatY) < 127))
      {servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,k);}//ブレーキ
      
      if ((PS3.getAnalogHat(LeftHatY) > 127)&&(PS3.getAnalogHat(LeftHatY) < 200)&&(PS3.getAnalogHat(RightHatY) > 127)&&(PS3.getAnalogHat(RightHatY) < 200))
      {servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,k);}//ブレーキ
//--------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
      if (PS3.getButtonPress(L1)){
        Serial.print(F("\r\nL1"));servo_write(8,190);

        if (PS3.getButtonClick(TRIANGLE)) {
        Serial.print(F("\r\nRight"));
        jj=!jj;
        digitalWrite(w21,jj);}else{}

        if (PS3.getButtonClick(CROSS)) {
        Serial.print(F("\r\nRight"));
        kk=!kk;
        digitalWrite(w22,kk);}else{}

        if (PS3.getButtonClick(CIRCLE)) {
        Serial.print(F("\r\nRight"));
        ll=!ll;
        digitalWrite(w23,ll);}else{}

        if (PS3.getButtonClick(SQUARE)) {
        Serial.print(F("\r\nRight"));
        mm=!mm;
        digitalWrite(w24,mm);}else{}

        if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nRight"));
        nn=!nn;
        digitalWrite(w25,nn);}else{}

        }//ｻｰﾎﾞ8出力
        
      if (PS3.getAnalogButton(L2) > 200)
      {servo_write(8,50);} //ｻｰﾎﾞ8出力
//-------------------------------------------------------------------------------------
      if (PS3.getButtonPress(R1)){
        Serial.print(F("\r\nR1"));servo_write(9,e);
        
        if (PS3.getButtonPress(UP)) {
        Serial.print(F("\r\nTraingle"));
        digitalWrite(w31,LOW);      //ピン出力
        }else{digitalWrite(w31,HIGH);}
        
        if (PS3.getButtonPress(DOWN)){
        Serial.print(F("\r\nCross"));
        digitalWrite(w32,LOW);      //ピン出力
        }else{digitalWrite(w32,HIGH);}
        
        if (PS3.getButtonClick(RIGHT)) {
        Serial.print(F("\r\nRight"));
        ii=ii+1;
        if(ii<3){dd=!dd;digitalWrite(w33,dd);}
        if((2<ii)&&(ii<5)){ee=!ee;digitalWrite(w34,ee);}
        if(3<ii){ii=0;}
        }else{}

        if (PS3.getButtonClick(LEFT)) {
        Serial.print(F("\r\nLeft"));
        hh=hh+1;
        if(hh<3){ff=!ff;digitalWrite(w35,ff);}
        if((2<hh)&&(hh<5)){gg=!gg;digitalWrite(w36,gg);}
        if(3<hh){hh=0;}
        }else{}
        
        }else{digitalWrite(w35,HIGH);digitalWrite(w36,HIGH);}//ｻｰﾎﾞ8出力
        
        if (PS3.getAnalogButton(R2) > 200)
      {servo_write(9,a);} //ｻｰﾎﾞ1出力

//-------------------------------------------------------------------------------
      //if(!digitalRead(w41)){digitalWrite(w15,LOW);}else{digitalWrite(w15,HIGH);}

//ＤＣモーター--------------------------------------------------------------------
      if (PS3.getButtonPress(TRIANGLE)&&!PS3.getButtonPress(L1)) {
        Serial.print(F("\r\nTraingle"));
        if (PS3.getButtonPress(CROSS)){}    //正転、逆転の短絡防止
          else{ while(digitalRead(w51)){digitalWrite(w11,LOW);digitalWrite(w13,LOW);}     }//ピン出力
        }
      else{digitalWrite(w11,HIGH);digitalWrite(w13,HIGH);}
      
      if (PS3.getButtonPress(CROSS)&&!PS3.getButtonPress(L1)){
        Serial.print(F("\r\nCross"));
        if (PS3.getButtonPress(TRIANGLE)){} //正転、逆転の短絡防止
          else{ while(digitalRead(w52)){digitalWrite(w12,LOW); digitalWrite(w14,LOW);}     }//ピン出力
        }
      else{digitalWrite(w12,HIGH);digitalWrite(w14,HIGH);}

      if (PS3.getButtonPress(CIRCLE)&&!PS3.getButtonPress(L1)) {
        Serial.print(F("\r\nCircle"));
        if (PS3.getButtonPress(SQUARE)){} //正転、逆転の短絡防止
          else{ digitalWrite(w11,LOW);digitalWrite(w13,LOW);      }//ピン出力
      }
      else{digitalWrite(w11,HIGH);digitalWrite(w13,HIGH);}
      
      if (PS3.getButtonPress(SQUARE)&&!PS3.getButtonPress(L1)){
        Serial.print(F("\r\nSquare"));
        if (PS3.getButtonPress(CIRCLE)){} //正転、逆転の短絡防止
          else{ digitalWrite(w12,LOW); digitalWrite(w14,LOW);      }//ピン出力
      }
      else{digitalWrite(w12,HIGH);digitalWrite(w14,HIGH);}

      if (PS3.getButtonClick(UP)&&!PS3.getButtonPress(R1)) {
        Serial.print(F("\r\nUp"));
        cc=h;    }//ピン出力
      else{cc==h;}
      
      if (PS3.getButtonClick(DOWN)&&!PS3.getButtonPress(R1)) {
        Serial.print(F("\r\nDown"));
        cc=i;    }//ピン出力
      else{cc==h;}
      
      if (PS3.getButtonPress(RIGHT)&&!PS3.getButtonPress(R1)) {
        Serial.print(F("\r\nRight"));
        digitalWrite(w26,LOW);      }//ピン出力
      else{digitalWrite(w26,HIGH);}
      
      if (PS3.getButtonPress(LEFT)&&!PS3.getButtonPress(R1)) {
        Serial.print(F("\r\nLeft"));
        digitalWrite(w27,LOW);      }//ピン出力
      else{digitalWrite(w27,HIGH);}

      if (PS3.getButtonPress(L3)) {
        Serial.print(F("\r\nL3"));
        digitalWrite(r1,Low);      }//ピン出力
      else{digitalWrite(r1,HIGH);}

      if (PS3.getButtonPress(R3)) {
        Serial.print(F("\r\nR3"));
        digitalWrite(r2,Low);      }//ピン出力
      else{digitalWrite(r2,HIGH);}

      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSELECT"));
        kaeri();      }//ピン出力
      else{  }

      if (PS3.getButtonClick(PS)) {
        Serial.print(F("\r\nSELECT"));
        iki1();      }//ピン出力
      else{  }

      if (PS3.getButtonClick(START)&&!PS3.getButtonPress(L1)) {
        Serial.print(F("\r\nSTART"));
        iki2();
        }//ピン出力
      else{  }

  }
}


void iki1(){
  delay_ms(2000);
  
  while(digitalRead(w41)||digitalRead(w42)){servo_write(0,cc);servo_write(1,k);servo_write(2,cc);servo_write(3,k);servo_write(4,cc);servo_write(5,k);servo_write(6,cc);servo_write(7,k);}
  servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,k);delay_ms(1000);
  while(digitalRead(w43)||digitalRead(w44)){servo_write(0,cc);servo_write(1,k);servo_write(2,k);servo_write(3,cc);servo_write(4,k);servo_write(5,cc);servo_write(6,cc);servo_write(7,k);}
  servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,k);delay_ms(1000);
  while(digitalRead(w45)||digitalRead(w46)){servo_write(0,k);servo_write(1,cc);servo_write(2,k);servo_write(3,cc);servo_write(4,k);servo_write(5,cc);servo_write(6,k);servo_write(7,cc);}
  servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,k);delay_ms(1000);
  servo_write(0,cc);servo_write(1,k);servo_write(2,cc);servo_write(3,k);servo_write(4,cc);servo_write(5,k);servo_write(6,cc);servo_write(7,k);delay_ms(500);
  servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,k);delay_ms(1000);
 
 
}


void iki2(){
  delay_ms(2000);
  
  while(digitalRead(w41)||digitalRead(w42)){servo_write(0,cc);servo_write(1,k);servo_write(2,cc);servo_write(3,k);servo_write(4,cc);servo_write(5,k);servo_write(6,cc);servo_write(7,k);}
  servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,k);delay_ms(1000);
  while(digitalRead(w47)||digitalRead(w48)){servo_write(0,k);servo_write(1,cc);servo_write(2,cc);servo_write(3,k);servo_write(4,cc);servo_write(5,k);servo_write(6,k);servo_write(7,cc);}
  servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,k);delay_ms(1000);
  while(digitalRead(w51)){digitalWrite(w11,LOW);digitalWrite(w13,LOW);}
  digitalWrite(w11,HIGH);digitalWrite(w13,HIGH);
  servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,k);
  
 
 
}

void kaeri(){
  delay_ms(2000);
  while(digitalRead(w52)){digitalWrite(w12,LOW); digitalWrite(w14,LOW);}
  digitalWrite(w12,HIGH);digitalWrite(w14,HIGH);
  servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,k);delay_ms(1000);
  while(digitalRead(w43)||digitalRead(w44)){servo_write(0,cc);servo_write(1,k);servo_write(2,k);servo_write(3,cc);servo_write(4,k);servo_write(5,cc);servo_write(6,cc);servo_write(7,k);}
  servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,k);delay_ms(1000);
  while(digitalRead(w45)||digitalRead(w46)){servo_write(0,k);servo_write(1,cc);servo_write(2,k);servo_write(3,cc);servo_write(4,k);servo_write(5,cc);servo_write(6,k);servo_write(7,cc);}
  servo_write(0,k);servo_write(1,k);servo_write(2,k);servo_write(3,k);servo_write(4,k);servo_write(5,k);servo_write(6,k);servo_write(7,k);delay_ms(1000);
  

  

}
