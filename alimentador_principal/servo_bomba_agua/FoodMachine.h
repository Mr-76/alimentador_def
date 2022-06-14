#ifndef FoodMachine_h
#define FoodMachine_h

#include "Arduino.h"
#include "Servo.h"

class FoodMachine

{

  public:

    FoodMachine(int pin,Servo servo,int angle_c,int angle_o);

    void open_exit();

    void close_exit();


  private:
    Servo _servo;
    int _pin;
    int _angle_c;
    int _angle_o;

};

#endif
