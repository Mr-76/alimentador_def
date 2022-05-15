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
	
	if (! RTC.isrunning())  { 
		Serial.println("RTC is NOT running!");
		//RTC.adjust(DateTime(__DATE__, __TIME__));
			
		//RTC.adjust(DateTime(2014, 1, 21, 3, 0, 0));
	}
	myservo.attach(D4);  
	RTC.adjust(DateTime(2022, 5, 14, 0, 0, 0));
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
	servo_tester(80,60,myservo);	
	ativado(5,12,18,5,now);
	watering_plants(6,30,3,now);

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
	delay(100);
	myservo.write(open_angle);
	delay(4000);
	Serial.println("Closing...");
	delay(100);
	myservo.write(close_angle);
	delay(4000);
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
*repeats the opening_and_closing function 
*@param seconds
*second that the servo stays in open
*position
*@param repeat
*times to repeat the function
*@param angle
*open angle
*@param fechado
*closing angle
@return void
*/
void function_repeater(int seconds,int repeat,int angle, int fechando){
	//funcao abre e fecha abertura do cano, seconds se refere ao tempo 
	//aberto em mili secs , repeat se refere ao numero de vezes 
	//para abrir e fechar a abertura e angle se refere ao angle de abertura
	for(int i = 0;i<repeat;i++)  {
		opening_and_closing(seconds,angle,fechando);
	}
	delay(70000); //delay para pular os minutes
	myservo.write(fechando);
}

/**
*opens and closes the opening 
*@param seconds
*second that the servo stays in open
*position
*@param angle
*opening angle
*@param fechado
*closing angle
@return void
*/
void opening_and_closing(int seconds,int angle,int fechado){
	//controlando a abertura do servo motor
	myservo.write(angle);
	delay(seconds);
	myservo.write(fechado); //fecha //closes
	delay(seconds);
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
void ativado(int hour1,int hour2,int hour3,int minutes,DateTime now){
	//ativa o servo a partir do tempo determinado
	int angle,repeat,tempo,fechado = (46,2,920,80);
	int timings_array[] = {hour1,hour2,hour3};
	int size_array = (sizeof(timings_array)/sizeof(int));//tamanho do array para loop
	for(int i = 0;i < size_array;i++){
		if ((now.hour()) == (timings_array[i])){
			if ((now.minute()) == (minutes)){
				function_repeater(tempo,repeat,angle,fechado);
			}
		}
		else{
			continue;
		}
	}
}
