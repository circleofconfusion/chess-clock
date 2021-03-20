#include "ClockDisplay.h"

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

ClockDisplay::ClockDisplay(int clock_pin, int data_pin, int latch_pin, int (&digit_pins)[4])
{
  this->clock_pin = clock_pin;
  this->data_pin = data_pin;
  this->latch_pin = latch_pin;
  this->digit_pins[0] = digit_pins[0];
  this->digit_pins[1] = digit_pins[1];
  this->digit_pins[2] = digit_pins[2];
  this->digit_pins[3] = digit_pins[3];
  this->active_digit = 0;
}

void ClockDisplay::update(int * clock_1_digits, int * clock_2_digits)
{
  digitalWrite(digit_pins[active_digit], HIGH);
  // advance to next digit
  if (active_digit == 3) {
    active_digit = 0;
  } else {
    active_digit++;
  }

  // set its segments through the shift register
  int digit1 = numbers[*(clock_1_digits + active_digit)];
  int digit2 = numbers[*(clock_2_digits + active_digit)];
  if (active_digit == 1) {
    // if 2nd digit, light the decimal point
    digit1 |= 0b00010000; 
    digit2 |= 0b00010000;
  }
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, LSBFIRST, digit1);
  shiftOut(data_pin, clock_pin, LSBFIRST, digit2);
  digitalWrite(latch_pin, HIGH);

  // light the digit
  digitalWrite(digit_pins[active_digit], LOW);
}
