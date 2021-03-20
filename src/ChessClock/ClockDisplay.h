#ifndef CLOCK_DISPLAY
#define CLOCK_DISPLAY

#include <Arduino.h>

class ClockDisplay
{
  private:
    int clock_pin;
    int data_pin;
    int latch_pin;
    int active_digit;
    int digit_pins[4];

  public:
    ClockDisplay(int clock_pin, int data_pin, int latch_pin, int (&digit_pins)[4]);
    void update(int clock_1_digits[4], int clock_2_digits[4]);
  
};

#endif
