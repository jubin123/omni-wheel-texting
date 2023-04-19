#include "Arduino.h"
#include "motor_driver.h"

motorDriver::motorDriver(int IN1,int IN2, int PWMPin){
  _IN1 = IN1;
  _IN2 = IN2;
  _PWMPin = PWMPin;
  pinMode(_IN1, OUTPUT);
  pinMode(_IN2, OUTPUT);
  pinMode(_PWMPin, OUTPUT);
}

void motorDriver::spin(char Dir, unsigned char PWM){
  switch (Dir){
    case -1:    // counterclockwise
      digitalWrite(_IN1, HIGH);
      digitalWrite(_IN2, LOW);
      analogWrite(_PWMPin, PWM);
      break;
    case 0:     // stationary
      digitalWrite(_IN1, LOW);
      digitalWrite(_IN2, LOW);
      digitalWrite(_PWMPin, LOW);
      break;
    case 1:     // clockwise
      digitalWrite(_IN1, HIGH);
      digitalWrite(_IN2, LOW);
      analogWrite(_PWMPin, PWM);
      break;
  }
}
