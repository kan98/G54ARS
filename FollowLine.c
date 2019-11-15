#include "Header.h"

void followLeanRight() {
	leftMotorSpeedFollow = lowerSpeed;
	rightMotorSpeedFollow = fasterSpeed;
}

void followLeanLeft() {
	leftMotorSpeedFollow = fasterSpeed;
	rightMotorSpeedFollow = lowerSpeed;
}

task followLine(){
	HTCS2readRawRGB(S3,true, r, g, b);
	long prevColour, prevPrevColour, prevPrevPrevColour;
	prevColour = prevPrevColour = prevPrevPrevColour = (g+b)/2;
	while (1) {
		while(currentState == FINDINGLINE || currentState == AVOIDLINE){
			HTCS2readRawRGB(S3,true, r, g, b);
			currentColour = (g+b)/2;
			if ((float)currentColour / prevPrevPrevColour < 0.7) {
				whiteToBlackCheck = true;
				if(currentState == FINDINGLINE) {
					currentState = FOLLOWLINE;
					leftMotorSpeedFollow = -15;
					rightMotorSpeedFollow = -15;
				}
				wait1Msec(500);
			} else {
				whiteToBlackCheck = false;
			}
			prevPrevPrevColour = prevPrevColour;
			prevPrevColour = prevColour;
			prevColour = currentColour;
		}

	followLeanLeft();
	HTCS2readRawRGB(S3,true, r, g, b);
	currentColour = (g+b)/2;
	datalogAddLong(0, currentColour);
	datalogClose();

	while(currentColour > baselineColourLine) {
		followLeanRight();
		HTCS2readRawRGB(S3,true, r, g, b);
		currentColour = (g+b)/2;
		writeDebugStreamLine ("%d", currentColour);
	}
}
abortTimeslice();
}
