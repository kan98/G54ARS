#include "Header.h"

void followLeanRight() {
	leftMotorSpeedFollow = lowerSpeed;
	rightMotorSpeedFollow = fasterSpeed;
}

void followLeanLeft() {
	leftMotorSpeedFollow = fasterSpeed;
	rightMotorSpeedFollow = lowerSpeed;
}

long blackLine, whiteLine;


task followLine(){
	HTCS2readRawRGB(S3,true, r, g, b);
	long prevColour, prevPrevColour, prevPrevPrevColour;
	prevColour = prevPrevColour = prevPrevPrevColour = (g+b)/2;
	while (1) {
		while(currentState == FINDINGLINE){
			HTCS2readRawRGB(S3,true, r, g, b);
			currentColour = (g+b)/2;
			if ((float)currentColour / prevPrevPrevColour < 0.7) {
				writeDebugStreamLine("prev: %d, current %d", prevColour, currentColour);
				currentState = FOLLOWLINE;
				leftMotorSpeedFollow = -10;
				rightMotorSpeedFollow = -10;
				blackLine = currentColour;
				whiteLine = prevPrevColour;
				wait1Msec(500);
			}
			prevPrevPrevColour = prevPrevColour;
			prevPrevColour = prevColour;
			prevColour = currentColour;
		}

		followLeanLeft();
		HTCS2readRawRGB(S3,true, r, g, b);
		currentColour = (g+b)/2;
		if (currentColour < whiteLine){
		blackLine = currentColour;
		}

		while(currentColour > blackLine) {
			followLeanRight();
			HTCS2readRawRGB(S3,true, r, g, b);
			currentColour = (g+b)/2;
		}
	}
	abortTimeslice();
}
