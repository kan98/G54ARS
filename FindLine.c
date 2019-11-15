#include "Header.h"

bool turnRight = true;
int timerLimit = 1500;

task findLine() {
	clearTimer(T1);
	while (1) {
		if(time1[T1] >= 1000){
			int randomNo = random(30);
			if (randomNo < 12) {
				randomNo = 12;}
			if(turnRight){
				leftMotorSpeedFind = randomNo;
				rightMotorSpeedFind = lowerSpeed;
				turnRight = false;
				timerLimit = 700;
				} else {
				leftMotorSpeedFind = lowerSpeed;
				rightMotorSpeedFind = fasterSpeed;
				turnRight = true;
				timerLimit = 1000;
			}
			clearTimer(T1);
		}
		abortTimeslice();
	}
}
