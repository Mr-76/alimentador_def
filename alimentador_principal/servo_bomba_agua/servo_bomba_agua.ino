#include "Servo.h"
#include <Wire.h>
#include "RTClib.h"
#include <Keypad.h>
/**
 *@file servo_bomba_agua.ino
 *
 *@mainpage Doxygen Exemple
 *
 *@section libraries Libraries
 *-servo,wire-rtclib-keypad.
 *
 *@section author Author
 *- Created by Mr-76
 */



RTC_DS1307 RTC; // objeto rtc relogio 
Servo myservo; // def o objeto servo se referindo ao servo motor
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
	myservo.attach(D4); // define que pin o servo esta conectado 
	RTC.adjust(DateTime(2022, 5, 14, 0, 0, 0));
}

//DateTime now = RTC.now(); //ser visto no escopo global colocar nas func depois

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
*Is a function that tests if the
*servo motor is working
*/
void servo_tester(int open_angle,int close_angle,Servo meu_servo){
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
	//liga o rele da bomba de agua
	//tempo de aguar em minutos
	if (now.hour() == hour && now.minute() == minute){
		digitalWrite(PINO_RELE,HIGH);
		delay(tempo_aguar*60000);
		digitalWrite(PINO_RELE,LOW);
  	}
}

/**
*repeats the abrindoeFechando function 
*@param segundos
*second that the servo stays in open
*position
*@param repeticao
*times to repeat the function
*@param angulo
*open angle
*@param fechado
*closing angle
@return void
*/
void repetidordeFuncao(int segundos,int repeticao,int angulo, int fechando){
	//funcao abre e fecha abertura do cano, segundos se refere ao tempo 
	//aberto em mili secs , repeticao se refere ao numero de vezes 
	//para abrir e fechar a abertura e angulo se refere ao angulo de abertura
	for(int i = 0;i<repeticao;i++)  {
		AbrindoeFechando(segundos,angulo,fechando);
	}
	delay(70000); //delay para pular os minutos
	myservo.write(fechando);
}

/**
*opens and closes the opening 
*@param segundos
*second that the servo stays in open
*position
*@param angulo
*opening angle
*@param fechado
*closing angle
@return void
*/
void AbrindoeFechando(int segundos,int angulo,int fechado){
	//controlando a abertura do servo motor
	myservo.write(angulo);
	delay(segundos);
	myservo.write(fechado); //fecha //closes
	delay(segundos);
}

/**
*activates the servo based on 
*4 timings
*@param hora1
*first hour timing
*@param hora2
*second hour timing
*@param hora3
*third hour timing
*@param minutos
*minuts timing
*@param DateTime
*receives a date time object
@return void
*/
void ativado(int hora1,int hora2,int hora3,int minutos,DateTime now){
	//ativa o servo a partir do tempo determinado
	int angulo = 46;
	int repeticao = 2;
	int tempo = 920;
	int fechado = 80;

	int array_horario[] = {hora1,hora2,hora3};
	int size_array = (sizeof(array_horario)/sizeof(int));//tamanho do array para loop
	for(int i = 0;i < size_array;i++){
		if ((now.hour()) == (array_horario[i])){
			if ((now.minute()) == (minutos)){
				repetidordeFuncao(tempo,repeticao,angulo,fechado);
			}
		}
		else{
			continue;
		}
	}
}

