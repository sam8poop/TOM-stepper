// includes
	#include <Arduino.h>

// vars
	// pins
		// out pins
			#define STEP_PIN 7
			#define DIR_PIN 8
			#define ENABLE_PIN 9
		// in dips
			#define DIR_DIP 4
			#define ENABLE_DIP 2
			#define ROT_MODE_DIP 5  
		// in pins
			#define BUTTON_PIN 3
	// other
		// config
			const int Micro_step_mode = 6400; // change to 200 for low steps per rev, 800 for normal steps per rev, 6400 for high steps per rev
			const int Deg = 180;
			const float Rpm = 60;

		// calc
			const int Rot_delay = 30000000.0 / (Rpm * Micro_step_mode);
			const int Steps_in_deg_mode = Micro_step_mode * (Deg / 360.0);
		
// enums
	enum Rot_modes {
		Continuous,
		Button
	};
// functions dec
	void Step();
	void Rotate(Rot_modes Mode = Continuous);

// interrupt service routines
	void enable() {
		digitalWrite(ENABLE_PIN, !digitalRead(ENABLE_DIP));
	}

// builtin functions
	void setup() {
		Serial.begin(115200);
		pinMode(STEP_PIN, OUTPUT);
		pinMode(DIR_PIN, OUTPUT);
		pinMode(ENABLE_PIN, OUTPUT);

		pinMode(BUTTON_PIN, INPUT_PULLUP);
		pinMode(DIR_DIP, INPUT_PULLUP);
		pinMode(ENABLE_DIP, INPUT_PULLUP);
		digitalWrite(DIR_PIN, LOW);
		digitalWrite(ENABLE_PIN, LOW);
		attachInterrupt(digitalPinToInterrupt(ENABLE_DIP), enable, CHANGE);
	}
	void loop() {
		Rotate();
	}

// function def
	void Step() {
		digitalWrite(STEP_PIN, HIGH);
		delayMicroseconds(Rot_delay);

		digitalWrite(STEP_PIN, LOW);
		delayMicroseconds(Rot_delay);
	}
	void Rotate(Rot_modes Mode) {
		if (Mode == Button) {
			if (!digitalRead(BUTTON_PIN)) {
				for (int i = 0; i < Steps_in_deg_mode; i++) {
					Step();
				}
				digitalWrite(DIR_PIN, !digitalRead(DIR_PIN));
				delay(100);
			}
		} else if (Mode == Continuous) {
			Step();
		}
	}
