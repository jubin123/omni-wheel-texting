/* 
 * Example program of driving 3 omni wheels in a holonomic robot configuration in an open loop
 * This program is for demonstration purposes only, since it runs in an open loop without encoder feedback it is not robust
 * 
 * Being open loop, the setpoint RPM calculations in calc_speed() are effectively meaningless. These are instead just values in the range of (0, 255)
 * Note that motor PWM signals don't scale linearly with RPM, as such closed-loop encoder feedback is required for robust control 
 * 
 * Runs on Arduino uno with l298n motor controllers
 * 
 * Copyright (c) 2022 Will Donaldson
 * MIT License (MIT)
 * www.willdonaldson.io
 */

String b; 
String strs[20];
int StringCount = 0;

 
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

#define PI 3.14159265
float R = 0.5; // robot wheel-base radius
int scaling_factor = 255;  // pseudo scaling factor, in open loop we can't accurately send RPM commands so instead this scales the PWM signal to a reasonable value in the range of [0, 255]

void setup() {
  Serial.begin(57600);  
}

void loop() {
  // drive robot in a square
 // calc_speed(1, 0, 0);
  //delay(1500);
  //calc_speed(0, 1, 0);
 // delay(1500);
  //calc_speed(-1, 0, 0);
  //delay(1500);
 // calc_speed(0, -1, 0);
  //delay(1500);
  while( Serial.available( ) )  
{ StringCount = 0; 
b = Serial.readString( );  
//Serial.println(b);

  // Split the string into substrings
  while (b.length() > 0)
  {
    int index = b.indexOf(' ');
    if (index == -1) // No space found
    {
      strs[StringCount++] = b;
      break;
    }
    else
    {
      strs[StringCount++] = b.substring(0, index);
      b = b.substring(index+1);
    }
  }

  // Show the resulting substrings
  /*for (int i = 0; i < StringCount; i++)
  {
    
    Serial.println(strs[i]);
    
  }*/

  calc_speed(strs[0].toFloat(),strs[1].toFloat(), strs[2].toFloat());
  //delay(1500);

}  
}

void calc_speed(float x_dot, float y_dot, float theta_dot){
  // calculates motor speeds for 3 wheel omni drive robot
  // see derivation of equations here: https://modernrobotics.northwestern.edu/nu-gm-book-resource/13-2-omnidirectional-wheeled-mobile-robots-part-1-of-2/
  float PWM1 = -R*theta_dot + x_dot ;
  float PWM2 = -R*theta_dot - 0.5*x_dot - sin(PI/3.0)*y_dot;
  float PWM3 = -R*theta_dot - 0.5*x_dot + sin(PI/3.0)*y_dot;
  
  int Dir1 = (PWM1 > 0) - (PWM1 < 0);   // returns -1 or 1
  int Dir2 = (PWM2 > 0) - (PWM2 < 0);
  int Dir3 = (PWM3 > 0) - (PWM3 < 0);

  PWM1 = (int)abs(PWM1*scaling_factor); // scale in PWM range of [0, 255]
  PWM2 = (int)abs(PWM2*scaling_factor);
  PWM3 = (int)abs(PWM3*scaling_factor);
  
  M1.spin(Dir1, PWM1);
  M2.spin(Dir2, PWM2);
  M3.spin(Dir3, PWM3);
}
