#include <Arduino.h>
// pins
#define STEP_PIN 7
#define DIR_PIN 8
#define ENABLE_PIN 9
#define DIR_DIP 3
#define ENABLE_DIP 4

// config
#define MICRO_STEP_MODE 6400 // change to 200 for low steps per rev, 800 for normal steps per rev, 6400 for high steps per rev
const int deg = 180;
const float rpm = 60;

// calc
const int rot_delay = 30000000.0 / (rpm * MICRO_STEP_MODE);
const int steps_in_deg_mode = MICRO_STEP_MODE * (deg / 360.0);
void setup() {
  Serial.begin(115200);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  pinMode(2, INPUT_PULLUP);
  pinMode(DIR_DIP, INPUT_PULLUP);
  pinMode(ENABLE_DIP, INPUT_PULLUP);
  digitalWrite(DIR_PIN,false);
  digitalWrite(ENABLE_PIN,false);
}

void loop() {
  digitalWrite(ENABLE_PIN, !digitalRead(ENABLE_DIP));

  if (true) { // for testing porpises, true/if for button + changing dir, false/else for continus rot.
    if (!digitalRead(2)) {
      for (int i = 0; i < steps_in_deg_mode; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(rot_delay);

        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(rot_delay);
      }
      digitalWrite(DIR_PIN, !digitalRead(DIR_PIN));
      delay(100);
    }
  }
  else {
    digitalWrite(DIR_PIN, !digitalRead(DIR_DIP));
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(rot_delay);

    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(rot_delay);
  }
}