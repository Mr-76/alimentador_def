#include <FoodMachine.h>
#include <Controller.h>
#include "Servo.h"
#include <Wire.h>
#include "RTClib.h"
#include <Keypad.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1);


/**
  @file servo_bomba_agua.ino

  @mainpage Servo_food_water Doc

  @section libraries Libraries

  Servo-version:1.1.7 by Arduino\n
  RTClib-version:2.0.2 by Adafruit\n
  Keypad-version:3.1.1 by Community,github/Chris-A/Keypad\n

  @section author Author
  - Created by Mr-76
*/

RTC_DS1307 RTC; //RTC object
Servo myservo; //servo object
int PINO_RELE = 5;
int timing_array[] = {9, 13, 19, 31};
const int Pinbutton1 = 12;
const int Pinbutton2 = 7;
const int Pinbutton3 = 4;
int button1 = 0;
int button2 = 0;
int button3 = 0;


Controller control(timing_array); FoodMachine foodMachine(myservo, 70, 110);

void setup() {
  control.setRepeat(3);//seting repeating time
  foodMachine.attach(5); //attach pin to  servo
  Serial.begin(57600);
  foodMachine.close_exit();//clsoe the exit when starting
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PINO_RELE, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(Pinbutton1, INPUT);
  pinMode(Pinbutton2, INPUT);
  pinMode(Pinbutton3, INPUT);


  if (! RTC.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    // while (1) delay(10);
  }

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    //	RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //RTC.adjust(DateTime(2022, 5, 17, 17, 11, 0));
  }
  //RTC.adjust(DateTime(2022, 5, 17, 17, 11, 0));
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


  int hora = int(now.hour());
  int minute1 = int(now.minute());
  int second1 = int(now.second());

  String horas = String(hora);

  String minutes1 = String(minute1);

  String seconds1 = String(second1);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 28);
  display.println(horas);
  display.setCursor(30, 28);
  display.println(minutes1);
  display.setCursor(70, 28);
  display.println(seconds1);
  display.display();
  delay(1000);
  //servo_tester(166,135,myservo);

  control.activate(now, foodMachine); // display not working if this is active :(


  //display_time(horas, minutes1, seconds1);//not working if contro active somehow fucion not working
  //servo_tester(166,135,myservo);
  Serial.println("out...");

  button2 = digitalRead(Pinbutton2);

  if (button2 == HIGH) {
    select_timings();
  }
}

/**
   displays the current timings in the system and lets u modify it.
   theres a 5 in the display for some reason >:()
*/
void select_timings() {
  Serial.println("MENU...");
  for (int i = 0; i < 4; i ++) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 28);
    display.println("CHANGE TIMINGS");
    display.display();
    delay(1000);
    while (true) {
      delay(200);
      button1 = digitalRead(Pinbutton1);
      button2 = digitalRead(Pinbutton2);
      button3 = digitalRead(Pinbutton3);

      String item = String(timing_array[i]);
      String index = String(i + 1);

      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 28);
      display.println(item);
      display.display();
      delay(900);


      if (button2 == HIGH) {
        Serial.println("press...");
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0, 28);
        display.println("NEXT");
        display.display();
        delay(500);
        break;
      } else if (button1 == HIGH) {
        timing_array[i]++;
        Serial.println(timing_array[i]);
        continue;
      } else if (button3 == HIGH) {
        timing_array[i]--;
        Serial.println(timing_array[i]);
        continue;

      } else {
        continue;
      }
    }
  }
  control.changeTiming(timing_array);
}

/**
  Tests if the servo motor is working
  @param open_angle
  angle to open the exit of food
  @param close_angle
  angle to close the exit of food
  @param my_servo
  Servo object to run the commands
  @return
  void
*/
void servo_tester(int open_angle, int close_angle, Servo my_servo) {
  Serial.println("Opening");


  my_servo.write(open_angle);
  delay(1000);
  Serial.println("Closing...");
  my_servo.write(close_angle);
  delay(1000);


}

/**
  water pump activation function
  @param hour
  hour to activate the pump
  @param minute
  minute to activate the pump
  @param tempo_aguar
  time of the pump on
  @param DateTime
  Receives a date time object
  @return void
*/
void watering_plants(int hour, int minute, int tempo_aguar, DateTime now) {
  if (now.hour() == hour && now.minute() == minute) {
    digitalWrite(PINO_RELE, HIGH);
    delay(tempo_aguar * 60000);
    digitalWrite(PINO_RELE, LOW);
  }
}

/**
  activates the servo based on
  4 timings
  @param hour1
  first hour timing
  @param hour2
  second hour timing
  @param hour3
  third hour timing
  @param minutes
  minuts timing
  @param DateTime
  receives a date time object
  @return void
*/
void ativado(int hour1, int hour2, int hour3, int minutes1, DateTime now, Servo my_servo) {
  Serial.println("function ativado");
  int angle  = 135;
  int repeat = 3;
  int timing = 1700;
  int closed = 166;
  int timings_array[] = {hour1, hour2, hour3};
  int size_array = (sizeof(timings_array) / sizeof(int)); //tamanho do array para loop
  for (int i = 0; i < size_array; i++) {
    if ((now.hour()) == (timings_array[i])) {
      Serial.println("function ativado inside 1");
      if ((now.minute()) == (minutes1)) {
        //Serial.println("function ativado inside 2");
        for (int repeat_times = 0; repeat_times < repeat; repeat_times++) {
          //Serial.println("repeater func1");
          activate_servo(angle, closed, myservo, timing);
          delay(1000);
        }
        delay(60000);//pass 1 min
        my_servo.write(closed);
      } else {
        break;
      }
    } else {
      continue;
    }
  }
}

/**
  Activates the servo
  @param open_angle
  angle to open the exit of food2
  @param close_angle
  angle to close the exit of food
  @param my_servo
  Servo object to run the commands
  @return
  void
*/
void activate_servo(int open_angle, int close_angle, Servo my_servo, int timing) {
  Serial.println("Opening");
  my_servo.write(open_angle);
  delay(timing);
  Serial.println("Closing...");
  my_servo.write(close_angle);
  delay(timing);
}
