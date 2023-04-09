#ifndef motordriver_h
#define motordriver_h

#include "Arduino.h"

class motorDriver {
public:
    motorDriver(int IN1, int IN2, int PWMPin);
    void spin(char Dir, unsigned char PWM);
private:
    int _PWMPin;
    int _IN1;
    int _IN2;
};

#endif
