#include "Servo.h"
#include <Wire.h>
#include "RTClib.h"
#include <Keypad.h>

/**
 *@file servo_bomba_agua.ino
 *
 *@mainpage Servo_food_water Doc
 *
 *@section libraries Libraries
 *
 *Servo-version:1.1.7 by Arduino\n
 *RTClib-version:2.0.2 by Adafruit\n
 *Keypad-version:3.1.1 by Community,github/Chris-A/Keypad\n
 *
 *@section author Author
 *- Created by Mr-76
 */

RTC_DS1307 RTC; //RTC object 
Servo myservo; //servo object
int PINO_RELE = 3;

void setup(){
	Serial.begin(57600);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(PINO_RELE,OUTPUT);
	
	
  if (! RTC.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // RTC.adjust(DateTime(year, month, day, hh, mm, ss));
  }
  
	myservo.attach(D4); 
  myservo.write(120);
}


void loop() {
	DateTime now = RTC.now();
	Serial.print(now.hour(), DEC);
	Serial.print(':');
	Serial.print(now.minute(), DEC);
	Serial.print(':');
	Serial.print(now.second(), DEC);
	Serial.println();
	delay(1000);
	//servo_tester(90,120,myservo);	
	ativado(5,12,19,31,now,myservo);
	//watering_plants(6,30,3,now);

}

/**
*Tests if the servo motor is working
*@param open_angle
*angle to open the exit of food
*@param close_angle
*angle to close the exit of food
*@param my_servo
*Servo object to run the commands
*@return
*void
*/

void servo_tester(int open_angle,int close_angle,Servo my_servo){

	Serial.println("Opening");
	//delay(2000);
	my_servo.write(open_angle);
	delay(920);
	Serial.println("Closing...");
	//delay(2000);
	my_servo.write(close_angle);
	delay(920);
	
}

/**
*water pump activation function
*@param hour
*hour to activate the pump
*@param minute
*minute to activate the pump
*@param tempo_aguar
*time of the pump on
*@param DateTime
*Receives a date time object
@return void
*/
void watering_plants(int hour,int minute,int tempo_aguar,DateTime now){
	if (now.hour() == hour && now.minute() == minute){
		digitalWrite(PINO_RELE,HIGH);
		delay(tempo_aguar*60000);
		digitalWrite(PINO_RELE,LOW);
  	}
}

/**
*activates the servo based on 
*4 timings
*@param hour1
*first hour timing
*@param hour2
*second hour timing
*@param hour3
*third hour timing
*@param minutes
*minuts timing
*@param DateTime
*receives a date time object
@return void
*/
void ativado(int hour1,int hour2,int hour3,int minutes1,DateTime now,Servo my_servo){
	//ativa o servo a partir do tempo determinado
    Serial.println("function ativado");
    
	int angle,repeat,tempo,fechado = (90,4,2000,120);//buggin >:
 
	int timings_array[] = {hour1,hour2,hour3};
	int size_array = (sizeof(timings_array)/sizeof(int));//tamanho do array para loop
	for(int i = 0;i < size_array;i++){
		if ((now.hour()) == (timings_array[i])){
			if ((now.minute()) == (minutes1)){
           Serial.println("repeater func");
           servo_tester(90,120,myservo); // create new loop >:
           servo_tester(90,120,myservo);
           delay(60000);
			}
		}
		else{
			continue;
		}
	}
}
