#include "CountdownClock.h"

int CLOCK_PIN = 10;
int LATCH_PIN = 11;
int DATA_PIN = 12;
int DIGIT_PINS[4] = {6, 7, 8, 9};

long last_update = millis();

CountdownClock cc_1 = {CLOCK_PIN, DATA_PIN, LATCH_PIN, DIGIT_PINS};

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

}

void loop() {
  long updateTimestamp = millis();
  if (updateTimestamp > last_update) {
    cc_1.update();
    last_update = updateTimestamp;
  }
}
