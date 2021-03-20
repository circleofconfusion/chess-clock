#include "CountdownClock.h"

// constructor
CountdownClock::CountdownClock()
{ 
  seconds = 0;
  minutes = 0;
  counting = false;
}

// private methods
void CountdownClock::count_second()
{
  seconds--;
  if (seconds < 0 && minutes > 0) {
    seconds = 59;
    minutes--;
  }
  else if (seconds < 0 && minutes == 0) {
    seconds = 0;
    counting = false;
  }  
}

// public methods
void CountdownClock::update()
{
  long count_timestamp = millis();
  if (counting && count_timestamp - 1000 > last_count_millis) {
    count_second();
    last_count_millis = count_timestamp;
  }
}

void CountdownClock::start()
{
  last_count_millis = millis();
  counting = true;
}

void CountdownClock::stop()
{
  counting = false;
}

void CountdownClock::reset()
{
  seconds = 0;
  minutes = 0;
}

void CountdownClock::add_seconds()
{
  if (!counting) seconds++;
}
void CountdownClock::add_seconds(int seconds)
{
  if (!counting) seconds += seconds;
}

void CountdownClock::subtract_seconds()
{
  if (!counting) this->seconds--;
}
void CountdownClock::subtract_seconds(int seconds)
{
  if (!counting) this->seconds -= seconds;
}

void CountdownClock::add_minutes()
{
  if (!counting) this->minutes++;
}
void CountdownClock::add_minutes(int minutes)
{
  if (!counting) this->minutes += minutes;
}

void CountdownClock::subtract_minutes()
{
  if (!counting) this->minutes--;
}
void CountdownClock::subtract_minutes(int minutes)
{
  if (!counting) this->minutes -= minutes;
}

int* CountdownClock::get_digits()
{
  int *digits{ new int[4]{minutes / 10, minutes % 10, seconds / 10, seconds % 10}};
  return digits;
}
