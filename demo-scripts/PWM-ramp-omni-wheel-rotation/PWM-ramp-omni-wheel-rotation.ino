/* 
 * Example program of driving 3 omni wheels in a PWM ramp to rotate holonomic robot on the spot in an open loop
 * Runs on Arduino uno with l298n motor controllers
 * 
 * Copyright (c) 2022 Will Donaldson
 * MIT License (MIT)
 * www.willdonaldson.io
 */
 
#include "motor_driver.h"

#define M1IN1 7
#define M1IN2 6
#define M2IN1 5
#define M2IN2 4
#define M3IN1 3
#define M3IN2 2

#define PWMPin1 11
#define PWMPin2 10
#define PWMPin3 9

motorDriver M1(M1IN1,M1IN2, PWMPin1);
motorDriver M2(M2IN1,M2IN2, PWMPin2);
motorDriver M3(M3IN1,M3IN2, PWMPin3);

int stallPWM = 30;
int stepDelay = 7;

void setup() {
}

void loop() {
  delay(1000);
  for(int i = stallPWM; i <= 255; i++){
    M1.spin(1, i);
    M2.spin(1, i);
    M3.spin(1, i);
    delay(stepDelay);
  }
  delay(1000);
  for(int i = 255; i >= stallPWM; i--){
    M1.spin(1, i);
    M2.spin(1, i);
    M3.spin(1, i);
    delay(stepDelay);
  }
}
