#include <Servo.h>
#include<Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC; // objeto rtc relogio 
Servo myservo; // def o objeto servo se referindo ao servo motor

int PINO_RELE = 3;
int angulo = 46;
int repeticao = 2;
int tempo = 920;
int fechado = 80;
float tempo_aguar = 360000;

void setup()   {
  pinMode(PINO_RELE,OUTPUT);
  Serial.begin(57600);
  RTC.begin();
  
  if (! RTC.isrunning())  { 
     Serial.println("RTC is NOT running!");
     // RTC.adjust(DateTime(__DATE__, __TIME__));
      // RTC.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  myservo.attach(2); // define que pin o servo esta conectado 
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
                 
  if (((now.hour() == 8) || (now.hour() == 10) || (now.hour() == 11) || (now.hour() == 14) || (now.hour() == 16)) && (now.minute() == 5)) {
    repetidordeFuncao(tempo,repeticao,angulo,fechado);
  }

  if (now.hour() == 6 && now.minute() == 30){
    digitalWrite(PINO_RELE,HIGH);
    delay(tempo_aguar);
    digitalWrite(PINO_RELE,LOW);
  }
}


void repetidordeFuncao(int segundos,int repeticao,int angulo, int fechando){
//funcao abre e fecha abertura do cano segundos se refere ao tempo aberto em mili secs , repeticao se refere ao numero de vezes 
//para abrir e fechar a abertura angulo se refere ao angulo de abertura
  for(int i = 0;i<repeticao;i++)  {
  AbrindoeFechando(segundos,angulo,fechado);
  }
  delay(70000);
  myservo.write(fechado);
}

void AbrindoeFechando(int segundos,int angulo,int fechado){
  myservo.write(angulo);
  delay(segundos);
  myservo.write(fechado); //fecha //closes
  delay(segundos);
}


