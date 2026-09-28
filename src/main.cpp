#include <Arduino.h>
// pins
#define STEP_PIN 7
#define DIR_PIN 8
#define ENABLE_PIN 9

#define DIR_DIP 4
#define ENABLE_DIP 2
#define ROT_MODE_DIP 5  

#define BUTTON_PIN 3

// config
const int Micro_step_mode = 6400; // change to 200 for low steps per rev, 800 for normal steps per rev, 6400 for high steps per rev
const int Deg = 180;
const float Rpm = 60;

// calc
const int Rot_delay = 30000000.0 / (Rpm * Micro_step_mode);
const int Steps_in_deg_mode = Micro_step_mode * (Deg / 360.0);

// enums
enum class rot_mode_modes {
	Continus,
	Button
};

// functions
void Rot_mode(rot_mode_modes Mode) {

}

// interrupt service routines
void enable() {
	digitalWrite(ENABLE_PIN, !digitalRead(ENABLE_DIP));
}


void setup() {
	attachInterrupt(digitalPinToInterrupt(ENABLE_DIP), enable, CHANGE);
	Serial.begin(115200);
	pinMode(STEP_PIN, OUTPUT);
	pinMode(DIR_PIN, OUTPUT);
	pinMode(ENABLE_PIN, OUTPUT);

	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(DIR_DIP, INPUT_PULLUP);
	pinMode(ENABLE_DIP, INPUT_PULLUP);
	digitalWrite(DIR_PIN, false);
	digitalWrite(ENABLE_PIN, false);
}

void loop() {


	if (true) { // for testing porpises, true/if for button + changing dir, false/else for continus rot.
		if (!digitalRead(BUTTON_PIN)) {
			for (int i = 0; i < Steps_in_deg_mode; i++) {
				digitalWrite(STEP_PIN, HIGH);
				delayMicroseconds(Rot_delay);

				digitalWrite(STEP_PIN, LOW);
				delayMicroseconds(rot_delay);
			}
			digitalWrite(DIR_PIN, !digitalRead(DIR_PIN));
			delay(100);
		}
	} else {
		digitalWrite(DIR_PIN, !digitalRead(DIR_DIP));
		digitalWrite(STEP_PIN, HIGH);
		delayMicroseconds(Rot_delay);

		digitalWrite(STEP_PIN, LOW);
		delayMicroseconds(rot_delay);
	}
}