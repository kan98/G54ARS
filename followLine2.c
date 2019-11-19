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
	baselineColourLine = prevColour = prevPrevColour = prevPrevPrevColour = (g+b)/2;
	baselineColourLine = baselineColourLine/3;
	while (1) {
		while(currentState == FINDINGLINE || currentState == AVOIDLINE){
			HTCS2readRawRGB(S3,true, r, g, b);
			currentColour = (g+b)/2;
			if ((float)currentColour / prevPrevPrevColour < 0.5) {
				whiteToBlackCheck = true;
				if(currentState == FINDINGLINE) {
					currentState = FOLLOWLINE;
					leftMotorSpeedFollow = -10;
					rightMotorSpeedFollow = -10;
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

		while(currentColour > baselineColourLine) {
			followLeanRight();
			HTCS2readRawRGB(S3,true, r, g, b);
			currentColour = (g+b)/2;
			writeDebugStreamLine ("%d", currentColour);
		}
	}
	abortTimeslice();
}
