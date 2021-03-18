#include "CountdownClock.h"

const byte numbers[10] = {
  0b11101011, // 0
  0b00001001, // 1
  0b11100101, // 2
  0b10101101, // 3
  0b00001111, // 4
  0b10101110, // 5
  0b11101110, // 6
  0b10001001, // 7
  0b11101111, // 8
  0b10101111 // 9
};

// private methods
void CountdownClock::decrementSecond()
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
     

void CountdownClock::updateDisplay()
{
  digitalWrite(digit_pins[active_digit], HIGH);
  // advance to next digit
  if (active_digit == 3) {
    active_digit = 0;
  } else {
    active_digit++;
  }

  // set its segments through the shift register
  int digit = numbers[getDigitValue()];
  if (active_digit == 1) digit |= 0b00010000; // if 2nd digit, light the decimal point
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, LSBFIRST, digit);
  digitalWrite(latch_pin, HIGH);

  // light the digit
  digitalWrite(digit_pins[active_digit], LOW);
}

int CountdownClock::getDigitValue() {
  switch(active_digit) {
    case 0:
      return minutes / 10;
    case 1:
      return minutes % 10;
    case 2: 
      return seconds / 10;
    case 3:
      return seconds % 10; 
  }
}

// public methods
CountdownClock::CountdownClock(int clock_pin, int data_pin, int latch_pin, int (&digit_pins)[4])
{
  this->clock_pin = clock_pin;
  this->data_pin = data_pin;
  this->latch_pin = latch_pin;
  this->digit_pins[0] = digit_pins[0];
  this->digit_pins[1] = digit_pins[1];
  this->digit_pins[2] = digit_pins[2];
  this->digit_pins[3] = digit_pins[3];
  this->active_digit = 0;
 
  seconds = 0;
  minutes = 0;
  counting = false;
}

void CountdownClock::update()
{
  long count_timestamp = millis();
  if (counting && count_timestamp - 1000 > last_count_millis) {
    decrementSecond();
    last_count_millis = count_timestamp;
  }
  updateDisplay();
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

void CountdownClock::add_second()
{
  if (!counting) seconds++;
}

void CountdownClock::subtract_second()
{
  if (!counting) seconds--;
}

void CountdownClock::add_minute()
{
  if (!counting) minutes++;
}

void CountdownClock::subtract_minute()
{
  if (!counting) minutes--;
}
