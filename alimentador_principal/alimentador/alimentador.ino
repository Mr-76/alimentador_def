#include <FoodMachine.h>
#include <Controller.h>
#include "Servo.h"
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1);


/**
*  @file alimentador.ino
*
*  @mainpage food_giver Doc
*
*  @section libraries Libraries
*
*  Servo-version:1.1.7 by Arduino\n
*  RTClib-version:2.0.2 by Adafruit\n
*  Adafruit GFX Library-version:1.10.13\n
*  Adafruit SSD1306-version 2.5.1\n
*  
*  @section author Author
*  - Created by Mr-76
*/

RTC_DS1307 RTC; 
Servo myservo; 
int timing_array[] = {5, 10, 13, 30};
const int Pinbutton1 = 12;
const int Pinbutton2 = 7;
const int Pinbutton3 = 4;
int button1 = 0;
int button2 = 0;
int button3 = 0;


Controller control(timing_array); 
FoodMachine foodMachine(myservo, 70, 110);

void setup() {
  Serial.begin(57600);
  control.setRepeat(2);//set repeating time of the machine to open
  foodMachine.attach(5);//attaching the pin to the servo
  foodMachine.close_exit();  //close the exit to be sure

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(Pinbutton1, INPUT);
  pinMode(Pinbutton2, INPUT);
  pinMode(Pinbutton3, INPUT);


  if (! RTC.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
  }

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    //	RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    RTC.adjust(DateTime(2022, 5, 17, 9, 49, 0));
  }
}


void loop() {

  DateTime now = RTC.now(); //rtc up.
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000);


  int hora = int(now.hour());//getting current hour.
  int minute1 = int(now.minute()); //getting current minute.
  int second1 = int(now.second()); //getting current second.

  String horas = String(hora);

  String minutes1 = String(minute1);

  String seconds1 = String(second1);

  display.clearDisplay();//showing current time in the display.
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

  control.activate(now, foodMachine); //calling controler activate the food giver.

  button2 = digitalRead(Pinbutton2); //Read button 2 to change the array of timings.

  if (button2 == HIGH) {
    select_timings();
  }
}

/**
* Lets you modify the current timings inside the array
* of timings,uses the 3 buttons to increase decrease or 
* select the next timing.
*
* The function lets u change each one of the times 
* individually using a for loop, the display shows
* the current timing inside the array and u can modify
* it.Pressing the middle button(button2 in my setup)
* will let u select the next timing to modify.
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
*  Use this function to test the servo
*  that you are using.
*
*  @param open_angle angle to open the exit of food
*  @param close_angle angle to close the exit of food
*  @param my_servo Servo object to run the commands
*  @return void
*/
void servo_tester(int open_angle, int close_angle, Servo my_servo) {
  Serial.println("Opening");
  my_servo.write(open_angle);
  delay(1000);
  Serial.println("Closing...");
  my_servo.write(close_angle);
  delay(1000);
}
