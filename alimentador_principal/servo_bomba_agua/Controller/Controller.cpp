#include "Arduino.h"
#include "Controller.h"

Controller::Controller(int timings[4])
{

  _timings[0] = timings[0];
  _timings[1] = timings[1];
  _timings[2] = timings[2];
  _timings[3] = timings[3];
};

void Controller::changeTiming(int timings[4]){
  _timings[0] = timings[0];
  _timings[1] = timings[1];
  _timings[2] = timings[2];
  _timings[3] = timings[3];

}


void Controller::setRepeat(int times)
{
  _times = times;
};

void Controller::setOpenTime(int duration)
{
  _duration = duration;
};

void Controller::activate(DateTime now,FoodMachine foodMachine)

{
  Serial.println("function ativado");
  int size_array = (sizeof(_timings)/sizeof(int));//tamanho do array para loop
  for(int i = 0;i < size_array;i++){
    if ((now.hour()) == (_timings[i])){
      Serial.println("Correct Hour");
      Serial.println(now.minute());
      Serial.println(_timings[3]);
      if ((now.minute()) == (_timings[3])){
        Serial.println("Correct minutes");
        for(int repeat_times = 0; repeat_times < _times; repeat_times++){
          Serial.println("repeater func");
          foodMachine.open_exit();
          delay(1000);
          foodMachine.close_exit();
          delay(1000);
        }
        delay(60000);
        foodMachine.close_exit();//ensure its closed
      }else{
        break;
      }
    }else{
      continue;
    }
  }
};
