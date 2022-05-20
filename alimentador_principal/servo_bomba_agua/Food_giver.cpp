#include "Food_giver.h"

Food_giver::Food_giver(int array_timing[5],int minute,Servo my_servo,DateTime now){
	this-> array_timing[5]=array_timing[5];
	this-> minute=minute;
	this-> myservo = myservo;
  this-> now = now; 
}

void Food_giver::set_timing(DateTime now){
  now = now;
}

void Food_giver::print1(){
  Serial.print(array_timing[0]);
  }
