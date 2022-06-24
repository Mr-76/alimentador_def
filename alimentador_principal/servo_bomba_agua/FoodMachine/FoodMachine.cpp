#include "Arduino.h"
#include "Servo.h"
#include "FoodMachine.h"


FoodMachine::FoodMachine(Servo servo,int angle_c,int angle_o)
{
  _servo = servo;
  _angle_c = angle_c;
  _angle_o = angle_o;
}

void FoodMachine::open_exit()
{
	for (int i = _angle_c;i <= _angle_o;i++){
		_servo.write(i);
		delay(15);
	}
  //_servo.write(_angle_o);
}

void FoodMachine::close_exit()
{
	for (int i = _angle_o;i >= _angle_c;i--){
		_servo.write(i);
		delay(15);
	}
  //_servo.write(_angle_c);
}

void FoodMachine::attach(int pin)
{
 _servo.attach(pin);
}
