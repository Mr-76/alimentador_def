#include "Arduino.h"
#include "Controller.h"

Controller::Controller(int timings[4])
{
  _timings[4] = timings;
};

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
 
};
