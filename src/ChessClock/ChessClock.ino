#include "CountdownClock.h"
#include "ClockDisplay.h"

int CLOCK_PIN = 10;
int LATCH_PIN = 11;
int DATA_PIN = 12;
int DIGIT_PINS[4] = {6, 7, 8, 9};

long last_update = millis();

CountdownClock cc_1 = {};
CountdownClock cc_2 = {};
ClockDisplay clock_display = {CLOCK_PIN, DATA_PIN, LATCH_PIN, DIGIT_PINS};

void setup() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  pinMode(DIGIT_PINS[0], OUTPUT);
  pinMode(DIGIT_PINS[1], OUTPUT);
  pinMode(DIGIT_PINS[2], OUTPUT);
  pinMode(DIGIT_PINS[3], OUTPUT);

  digitalWrite(DIGIT_PINS[0], HIGH);
  digitalWrite(DIGIT_PINS[1], HIGH);
  digitalWrite(DIGIT_PINS[2], HIGH);
  digitalWrite(DIGIT_PINS[3], HIGH);

  cc_1.add_minutes(10);
  cc_2.add_minutes(10);
  
  cc_1.start();
}

void loop() {
  long updateTimestamp = millis();
  if (updateTimestamp > last_update) {
    cc_1.update();
    cc_2.update();
    int * cc_1_digits = cc_1.get_digits();
    int * cc_2_digits = cc_2.get_digits();
    clock_display.update(cc_1_digits,cc_2_digits);
    delete[] cc_1_digits;
    delete[] cc_2_digits;
    last_update = updateTimestamp;
  }
}
