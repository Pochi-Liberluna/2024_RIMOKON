#include"move.h"

int speed = "255";

const int RF_R = 2;  //左前
const int LF_R = 4;
const int RB_R = 5;  //左後ろ
const int LB_R = 12;
const int RF_L = 13;  //右前
const int LF_L = 16;
const int RB_L = 17;  //右後ろ
const int LB_L = 18;


void move::moveForward(){
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);
        digitalWrite(motor3Pin1, HIGH);
        digitalWrite(motor3Pin2, LOW);
        digitalWrite(motor4Pin1, HIGH);
        digitalWrite(motor4Pin2, LOW);
}
void move::moveRight(){
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
        digitalWrite(motor3Pin1, LOW);
        digitalWrite(motor3Pin2, LOW);
        digitalWrite(motor4Pin1, HIGH);
        digitalWrite(motor4Pin2, LOW);
}
void move::moveLeft(){
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);
        digitalWrite(motor3Pin1, HIGH);
        digitalWrite(motor3Pin2, LOW);
        digitalWrite(motor4Pin1, LOW);
        digitalWrite(motor4Pin2, LOW);
}
void move::moveBack(){
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, HIGH);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
        digitalWrite(motor3Pin1, LOW);
        digitalWrite(motor3Pin2, HIGH);
        digitalWrite(motor4Pin1, LOW);
        digitalWrite(motor4Pin2, HIGH);
}
void move::turnRight(){
// 右回転
}
void move::turnLeft(){
// 左回転
}