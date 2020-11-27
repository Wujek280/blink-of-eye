/**
 * Nakurwiator
 */
#include "Arduino.h"

#define D_13_LED 13
#define D_12 12
#define A_7 7

const int READING_TIMES = 10;
const int READING_THRESHOLD = 700;
const int MILLIS_MIN = 100;

int lastReading = 0;
int lastState = LOW;
int lastTriggerMillis = 0;

void setup()
{
	pinMode(D_13_LED, OUTPUT);
	pinMode(D_12, OUTPUT); /** invert */
	pinMode(A_7, INPUT);
	// Serial.begin(9600);
	// Serial.println("Current : " + (String)(currentReading) + "\tDelta : " + (String)(currentReading - lastReading));
}

void loop() {

	int readingSum = 0;
	int currentReading = 0;

	for (int i = 0; i < READING_TIMES; i++)
	{
		readingSum += analogRead(A_7);
	}

	currentReading = readingSum / READING_TIMES;

	lastReading = currentReading;

	if(READING_THRESHOLD < currentReading && READING_THRESHOLD < lastReading){
		if( (millis() - lastTriggerMillis()) < MILLIS_MIN){
			digitalWrite(D_13_LED, LOW );
			digitalWrite(D_12, HIGH );
			lastTriggerMillis = millis();
			lastState = HIGH;
		}
	}else{
		digitalWrite(D_13_LED, HIGH );
		digitalWrite(D_12, LOW );
  		lastState = LOW;
	}
}