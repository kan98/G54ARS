#include "Header.h"

long baselineColourLine = 425;

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
			if ((float)currentColour / prevPrevPrevColour < 0.5) {
				whiteToBlackCheck = true;
				if(currentState == FINDINGLINE) {
					currentState = FOLLOWLINE;
					leftMotorSpeedFollow = 20;
					rightMotorSpeedFollow = 0;
					wait1Msec(500);
					while (currentColour < PrevPrevColour){
						HTCS2readRawRGB(S3,true, r, g, b);
						currentColour = (g+b)/2;
						leftMotorSpeedFollow = 0;
						rightMotorSpeedFollow = 20;
					}
				}
				} else {
				whiteToBlackCheck = false;
			}
			prevPrevPrevColour = prevPrevColour;
			prevPrevColour = prevColour;
			prevColour = currentColour;
			wait1Msec(100);
		}
		startObserve = true;
		followLeanLeft();
		HTCS2readRawRGB(S3,true, r, g, b);
		currentColour = (g+b)/2;
		while(currentColour > baselineColourLine) {
			followLeanRight();
			HTCS2readRawRGB(S3,true, r, g, b);
			currentColour = (g+b)/2;
		}
	}
	abortTimeslice();
}
