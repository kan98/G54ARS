#include "Header.h"

bool turnRight = true;

task findLine() {
	clearTimer(T1);
	while (1) {
		if(time1[T1] >= 1000){
			int randomNo = random(30);
			if (randomNo < 14) {
				randomNo = 14;}
			if(turnRight){
				leftMotorSpeedFind = randomNo;
				rightMotorSpeedFind = lowerSpeed;
				turnRight = false;
			} else {
				leftMotorSpeedFind = lowerSpeed;
				rightMotorSpeedFind = randomNo;
				turnRight = true;
			}
			clearTimer(T1);
		}
		abortTimeslice();
	}
}
