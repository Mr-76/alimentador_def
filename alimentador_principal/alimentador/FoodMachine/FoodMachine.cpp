#include "Arduino.h"
#include "Servo.h"
#include "FoodMachine.h"

/**
 * Constructor to the food machine object.
 * @param servo a servo object 
 * @param angle_c angle of closing
 * @param angle_o angle of opening.
 */
FoodMachine::FoodMachine(Servo servo,int angle_c,int angle_o)
{
  _servo = servo;
  _angle_c = angle_c;
  _angle_o = angle_o;
}

/**
 * Opens the exit of food using the specified angle,
 * in a slowly way.
 * 
 */
void FoodMachine::open_exit()
{
	for (int i = _angle_c;i <= _angle_o;i++){
		_servo.write(i);
		delay(15);
	}
  //_servo.write(_angle_o); old
}

/**
 * Closes the exist for food using the specified angle,
 * in a slowly way.
 */
void FoodMachine::close_exit()
{
	for (int i = _angle_o;i >= _angle_c;i--){
		_servo.write(i);
		delay(15);
	}
}
/**
 * Attach pin to servo object.
 * @param pin pin to attach to the servo.
 */
void FoodMachine::attach(int pin)
{
 _servo.attach(pin);
}
