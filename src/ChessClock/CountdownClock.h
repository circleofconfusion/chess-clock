#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <Arduino.h>

class CountdownClock
{

  private:
    int seconds;
    int minutes;
    bool counting;
    long last_count_millis;

    void count_second();

  public:
    CountdownClock();
    void start();
    void stop();
    void reset();
    void add_seconds();
    void add_seconds(int seconds);
    void subtract_seconds();
    void subtract_seconds(int seconds);
    void add_minutes();
    void add_minutes(int minutes);
    void subtract_minutes();
    void subtract_minutes(int minutes);
    void update();
    int* get_digits();
};

#endif
