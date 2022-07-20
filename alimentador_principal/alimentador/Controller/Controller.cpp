#include "Arduino.h"
#include "Controller.h"

/**
 * Controller class, controls the opening and
 * closing of the exit of food on the little 
 * project.
 *
 * @param timings[4] A array of timings to activate the
 * 		     servo, and let the food out,the
 * 		     first 3 elements are hours and the 
 * 		     4th one its the minute.
 */
Controller::Controller(int timings[4])
{

  _timings[0] = timings[0];
  _timings[1] = timings[1];
  _timings[2] = timings[2];
  _timings[3] = timings[3];
};

/**
 * This method enables you to change the current timings
 * on stored on the array of timings.
 *
 * @param timings[4] A Array of timigns to activate the
 * 		     servo, and let the food out.
 */
void Controller::changeTiming(int timings[4]){
  _timings[0] = timings[0];
  _timings[1] = timings[1];
  _timings[2] = timings[2];
  _timings[3] = timings[3];

}

/**
 * This method can set the amount of times
 * a user want the action of opening and 
 * closing of the food exit.
 *
 * @param times Ammount of times to open
 * 		and close the exit of food.
 */
void Controller::setRepeat(int times)
{
  _times = times;
};

/**
 * This method sets the amount of time the food
 * exist shoud stay open.
 *
 * @param duration Duration in secs to let the exit
 * 		   of food open.
 */
void Controller::setOpenTime(int duration)
{
  _duration = duration;
};


/**
 * This method activates the opening of the exit of food and closing
 * if the current time is the same as the ones set up in the array of
 * timings created.
 *
 * @param now A date time object the rtc
 * @param foodMachine the servo currently in use.
 */
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
