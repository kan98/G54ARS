#include "Header.h"

int weightedSum(int weakWeight, int strongWeight){
	return (weakWeight*0.1) + (strongWeight*0.9);
}

bool rotate = false;
bool foundLine = false;

int turnSpeed  = 16;
int lowerSpeedAvoid = 8;

void avoidLeanRight() {
	leftMotorSpeedAvoid = lowerSpeedAvoid;
	rightMotorSpeedAvoid = turnSpeed;
}

void avoidLeanLeft() {
	leftMotorSpeedAvoid = turnSpeed;
	rightMotorSpeedAvoid = lowerSpeedAvoid;
}

void avoidSetMotorSpeed(int A, int C){
	leftMotorSpeedAvoid = A;
	rightMotorSpeedAvoid = C;
}

void avoidStraight(){
	avoidSetMotorSpeed(20, 20);
}

void backUp(){
	clearTimer(T1);
	avoidSetMotorSpeed(-20, -20);
	while(time1[T1] < 500){}
}

void rotateRobot(int direction = 0 /* left */) {
	resetGyro(S1);
	while (abs(getGyroDegrees(S1)) < 60) {
		if(direction == 0){
			avoidSetMotorSpeed(turnSpeed, 0);
			} else {
			avoidSetMotorSpeed(0, turnSpeed);
		}
	}
	avoidStraight();
	wait1Msec(1000);
	resetGyro(S1);
	while (abs(getGyroDegrees(S1)) < 60) {
		if(direction == 0){
			avoidSetMotorSpeed(0, turnSpeed);
			} else {
			avoidSetMotorSpeed(turnSpeed, 0);
		}
	}
	avoidStraight();
	wait1Msec(2000);
	rotate = true;
}

void checkForLine(){
	HTCS2readRawRGB(S3,true, r, g, b);
	currentColour = (g+b)/2;
	if (whiteToBlackCheck) {
		foundLine = true;
		backUp();
		currentState = FOLLOWLINE;
	}
}

task avoidLine() {
	float prevDistanceL, prevPrevDistanceL, prevDistanceR, prevPrevDistanceR;
	prevDistanceL = prevPrevDistanceL = getUSDistance(S4);
	prevDistanceR = prevPrevDistanceR = getUSDistance(S2);
	while (1){
		float distanceL = getUSDistance(S4);
		float distanceR = getUSDistance(S2);

		if (currentState != AVOIDLINE){
			if  ((distanceL+prevDistanceL+prevPrevDistanceL)/3 <= 8 || (distanceR+prevDistanceR+prevPrevDistanceR)/3 <=8){
				rotate = false;
				currentState = AVOIDLINE;
				backUp();
			}

		} else {
			while(!foundLine){

				if (distanceR < distanceL) {
					if (!rotate){
						rotateRobot();
					}

					if(weightedSum(getUSDistance(S4), getUSDistance(S2)) > 30){
						avoidLeanRight();
						checkForLine();
						}else {
						avoidLeanLeft();
						wait1Msec(1500);
					}
				}
				else {
					if (!rotate){
						rotateRobot(1);
					}

					if(weightedSum(getUSDistance(S2), getUSDistance(S4)) > 30){
						avoidLeanLeft();
						checkForLine();
						}else {
						avoidLeanRight();
						wait1Msec(1500);
					}
				}
				if (getUSDistance(S2) <= 5 || getUSDistance(S4) <= 5){
					backUp();
				}
			}
		}
		prevPrevDistanceL = prevDistanceL;
		prevDistanceL = distanceL;
		prevPrevDistanceR = prevDistanceR;
		prevDistanceR = distanceR;
	}
}
