#include "Header.h"

int weightedSum(int strongWeight, int weakWeight){
	return (weakWeight*0.9) + (strongWeight*0.1);
}

bool rotate = false;
bool foundLine = false;

int turnSpeed  = 16;
int lowerSpeedAvoid = 10;

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
	avoidSetMotorSpeed(-10, -10);
	while(time1[T1] < 500){}
}

void rotateRobot(int direction = 0 /* left */) {
	resetGyro(S1);
	while (abs(getGyroDegrees(S1)) < 52) {
		if(direction == 0){
			avoidSetMotorSpeed(turnSpeed, 0);
			} else {
			avoidSetMotorSpeed(0, turnSpeed);
		}
	}
	avoidStraight();
	wait1Msec(1700);
	resetGyro(S1);
	while (abs(getGyroDegrees(S1)) < 60) {
		if(direction == 0){
			avoidSetMotorSpeed(0, turnSpeed);
			} else {
			avoidSetMotorSpeed(turnSpeed, 0);
		}
	}
	avoidStraight();
	wait1Msec(2500);
	rotate = true;
}

void checkForLine(){
	HTCS2readRawRGB(S3,true, r, g, b);
	currentColour = (g+b)/2;
	if (whiteToBlackCheck) {
		foundLine = true;
		currentState = FOLLOWLINE;
	}
}

task avoidLine() {
	float prevDistanceL, prevPrevDistanceL, prevDistanceR, prevPrevDistanceR;
	prevDistanceL = prevPrevDistanceL = getUSDistance(S4);
	prevDistanceR = prevPrevDistanceR = getUSDistance(S2);
	float distanceL, distanceR;
	while (1){
		distanceL = getUSDistance(S4);
		distanceR = getUSDistance(S2);

		if (currentState != AVOIDLINE){
			if  ((distanceL+prevDistanceL+prevPrevDistanceL)/3 <= 5 || (distanceR+prevDistanceR+prevPrevDistanceR)/3 <= 5){
				rotate = false;
				foundLine = false;
				whiteToBlackCheck = false;
				currentState = AVOIDLINE;
				backUp();
			}
			prevPrevDistanceL = prevDistanceL;
			prevDistanceL = distanceL;
			prevPrevDistanceR = prevDistanceR;
			prevDistanceR = distanceR;

			} else {
			while(!foundLine){

				if (distanceR < distanceL) {
					if (!rotate){
						rotateRobot();
					}

					if(weightedSum(getUSDistance(S2), getUSDistance(S4)) > 30){
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

					if(weightedSum(getUSDistance(S4), getUSDistance(S2)) > 30){
						avoidLeanLeft();
						checkForLine();
						}else {
						avoidLeanRight();
						wait1Msec(1500);
					}
				}
			}
		}
	}
}
