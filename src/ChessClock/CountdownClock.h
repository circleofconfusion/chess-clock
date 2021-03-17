#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <Arduino.h>

class CountdownClock
{

  private:
    int clock_pin;
    int data_pin;
    int latch_pin;
    int active_digit;
    int digit_pins[4];
    
    int seconds;
    int minutes;
    bool counting;
    long last_count_millis;
    
    void decrementSecond();
    void updateDisplay();
    int getDigitValue();

  public:
    CountdownClock(int clock_pin, int data_pin, int latch_pin, int (&digit_pins)[4]);
    void start();
    void stop();
    void reset();
    void add_second();
    void subtract_second();
    void add_minute();
    void subtract_minute();
    void update();
};

#endif
