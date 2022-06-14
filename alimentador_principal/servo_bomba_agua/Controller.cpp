#include "Arduino.h"
#include "Controller.h"

Controller::Controller(int[4] timings)
{
  _timings = timings;
}

void setRepeat(int times)
{
  _times = times;
}

void setOpenTime(int duration)
{
  _duration = duration;
}

void activate(DateTime now,FoodMachine foodMachine)
{
  Serial.println("activating");
  int size_array = (sizeof(timings_array)/sizeof(int));//tamanho do array para loop
  for(int i = 0;i < size_array;i++){
    if ((now.hour()) == (timings_array[i])){
      Serial.println("function ativado inside 1");
      if ((now.minute()) == (minutes1)){
        //Serial.println("function ativado inside 2");
        for(int repeat_times = 0; repeat_times < repeat; repeat_times++){
          //Serial.println("repeater func1");
          activate_servo(angle,closed,myservo,timing); 
          delay(1000);
        }
        delay(60000);//pass 1 min
        my_servo.write(closed);
      }else{
        break;
      }
    }else{
      continue;
    }
  }  
}
