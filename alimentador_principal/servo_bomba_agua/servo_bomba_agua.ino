#include "Servo.h"
#include <Wire.h>
#include "RTClib.h"
#include <Keypad.h>

RTC_DS1307 RTC; // objeto rtc relogio 
Servo myservo; // def o objeto servo se referindo ao servo motor
int PINO_RELE = 3;

void setup(){
  Serial.begin(57600);
  pinMode(LED_BUILTIN, OUTPUT);
	pinMode(PINO_RELE,OUTPUT);
	
  #ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
  #endif
  if (! RTC.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
	myservo.attach(D4); // define que pin o servo esta conectado 
}

DateTime now = RTC.now(); //nao pode programa buga usar em funcçao para funcionar

void loop() {
	DateTime now = RTC.now();
	Serial.print(now.hour(), DEC);
	Serial.print(':');
	Serial.print(now.minute(), DEC);
	Serial.print(':');
	Serial.print(now.second(), DEC);
	Serial.println();
	delay(1000);
	
	ativado(5,9,18,10);
	watering_plants(6,30,3);

}

void watering_plants(int hour,int minute,int tempo_aguar){
	//liga o rele da bomba de agua
	//tempo de aguar em minutos
	if (now.hour() == hour && now.minute() == minute){
		digitalWrite(PINO_RELE,HIGH);
		delay(tempo_aguar*60000);
		digitalWrite(PINO_RELE,LOW);
  	}
}

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

void AbrindoeFechando(int segundos,int angulo,int fechado){
	//controlando a abertura do servo motor
	myservo.write(angulo);
	delay(segundos);
	myservo.write(fechado); //fecha //closes
	delay(segundos);
}

void ativado(int hora1,int hora2,int hora3,int minutos){
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
