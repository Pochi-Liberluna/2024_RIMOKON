#include"move.h"
// #include<Arduino.h>
// #include"Arduino.h"

const int motor1Pin1 = 2;  //左前
const int motor1Pin2 = 3;
const int motor2Pin1 = 4;  //左後ろ
const int motor2Pin2 = 5;
const int motor3Pin1 = 6;  //右前
const int motor3Pin2 = 7;
const int motor4Pin1 = 8;  //右後ろ
const int motor4Pin2 = 9;

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
