#include "Arduino.h"
#include "Servo.h"
#include "FoodMachine.h"


FoodMachine::FoodMachine(int pin,Servo servo,int angle_c,int angle_o)
{
  _pin = pin;
  _servo = servo;
  _servo.attach(_pin);
  _angle_c = angle_c;
  _angle_o = angle_o;
}

void FoodMachine::open_exit()
{
  _servo.write(_angle_o);
}

void FoodMachine::close_exit()
{
  _servo.write(_angle_c);
}
