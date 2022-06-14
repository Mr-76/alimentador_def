#ifndef Controller_h
#define Controller_h

#include "Arduino.h"

class Controller

{

  public:

    Controller(int[4] timings);

    void activate(DateTime now,FoodMachine foodMachine);

    void setRepeat(int times);

    void setOpenTime(int duration);


  private:
    int[4] _timings;
    int _times;
    int _duration;

};

#endif
