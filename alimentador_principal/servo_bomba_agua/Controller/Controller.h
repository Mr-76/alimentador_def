#ifndef Controller_h
#define Controller_h

#include "Arduino.h"
#include "RTClib.h"
#include "FoodMachine.h"

class Controller

{

  public:

    Controller(int timings[4]);

    void activate(DateTime now,FoodMachine foodMachine);

    void setRepeat(int times);

    void setOpenTime(int duration);


  private:
    int _timings[4];
    int _times;
    int _duration;

};

#endif
