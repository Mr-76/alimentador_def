#ifndef MY_FOOD_GIVER_H
#define MY_FOOD_GIVER_H
#include <Arduino.h>
#include "Servo.h"
#include <Wire.h>
#include "RTClib.h"
#include <Keypad.h>

class Food_giver{

	private:
		int array_timing[];
		int minute;
		Servo myservo;
    
	
	public:
    DateTime now;
		Food_giver(int array_timing[5],int minute,Servo my_servo,DateTime now);
		void set_timing(DateTime now);
    void print1();

};
#endif
