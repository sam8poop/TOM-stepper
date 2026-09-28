#include <Arduino.h>
#define STEP_PIN 7
#define DIR_PIN 8
#define ENABLE_PIN 9
#define DIR_DIP 3
#define ENABLE_DIP 4
// change to 200 for low steps per rev, 800 for normal steps per rev, 6400 for high steps per rev
#define MICRO_STEP_MODE 6400
int speed = 500;
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

  if (true) {
    if (!digitalRead(2)) {
      for (int i = 0; i < MICRO_STEP_MODE; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(500);

        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(500);
      }
      digitalWrite(DIR_PIN, !digitalRead(DIR_PIN));
      delay(100);
    }
  }
  else {
    digitalWrite(DIR_PIN, !digitalRead(DIR_DIP));
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(speed);

    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(speed);
    

  }
  
}