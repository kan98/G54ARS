#include "Header.h"

int weightedSum(int weakWeight, int strongWeight){
	return (weakWeight*0.1) + (strongWeight*0.9);
}

bool rotate = false;
bool foundLine = false;

int turnSpeed  = 15;
int lowerSpeedAvoid = 4;

void avoidPivotRight() {
	leftMotorSpeedAvoid = 0;
	rightMotorSpeedAvoid = 50;
}

void avoidPivotLeft() {
	leftMotorSpeedAvoid = 50;
	rightMotorSpeedAvoid = 0;
}

void avoidTurnLeft(){
	leftMotorSpeedAvoid = turnSpeed;
	rightMotorSpeedAvoid = lowerSpeed;
}

void avoidTurnRight(){
	leftMotorSpeedAvoid = lowerSpeed;
	rightMotorSpeedAvoid = turnSpeed;
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
	while (abs(getGyroDegrees(S1)) < 75) {
		if(direction == 0){
			avoidSetMotorSpeed(turnSpeed, 0);
			} else {
			avoidSetMotorSpeed(0, turnSpeed);
		}
	}
	avoidStraight();
	wait1Msec(1000);
	resetGyro(S1);
	while (abs(getGyroDegrees(S1)) < 75) {
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
	if (currentColour < baselineColourLine) {
		foundLine = true;
		currentState = FOLLOWLINE;
		backUp();
	}
}

task avoidLine()
{
	float prevDistanceL, prevPrevDistanceL, prevDistanceR, prevPrevDistanceR;
	prevDistanceL = prevPrevDistanceL = getUSDistance(S4);
	prevDistanceR = prevPrevDistanceR = getUSDistance(S2);
	while (1){
		float distanceL = getUSDistance(S4);
		float distanceR = getUSDistance(S2);

		if  ((distanceR+prevDistanceR+prevPrevDistanceR)/3 <= 8 || (distanceR+prevDistanceR+prevPrevDistanceR)/3 <= 8){
			foundLine = false;
			rotate = false;
			currentState = AVOIDLINE;
			backUp();


			while(!foundLine){

				if (distanceR < distanceL) {
					if (!rotate){
						rotateRobot();
					}
					resetGyro(S1);
					while (abs(getGyroDegrees(S1)) < 45){
						avoidPivotRight();
					}

					resetGyro(S1);

					if(weightedSum(getUSDistance(S4), getUSDistance(S2)) > 30){
						while (abs(getGyroDegrees(S1)) < 45){
							avoidPivotLeft();
						}
						avoidStraight();
						wait1Msec(500);
					}
					else{
						avoidTurnRight();
					}

					wait1Msec(1000);
				}
				if  (getUSDistance(S2) <= 5 || getUSDistance(S4) <= 5){
					backUp();
				}

				else {
					if (!rotate){
						rotateRobot(1);
					}

					if(weightedSum(getUSDistance(S2), getUSDistance(S4)) > 30){
						avoidPivotLeft();
						checkForLine();
						}else {
						avoidPivotRight();
						wait1Msec(1000);
					}
					if (getUSDistance(S2) <= 5 || getUSDistance(S4) <= 5){
						backUp();
					}
				}
			}
		}
		prevPrevDistanceL = prevDistanceL;
		prevDistanceL = distanceL;
		prevPrevDistanceR = prevDistanceR;
		prevDistanceR = distanceR;
	}
}
