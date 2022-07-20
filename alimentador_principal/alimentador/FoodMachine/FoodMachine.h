#ifndef FoodMachine_h
#define FoodMachine_h

#include "Arduino.h"
#include "Servo.h"
#include "RTClib.h"



class FoodMachine

{

  public:

    FoodMachine(Servo servo,int angle_c,int angle_o);

    void open_exit();

    void close_exit();

    void attach(int pin);

  private:
    Servo _servo;
    int _angle_c;
    int _angle_o;

};

#endif
