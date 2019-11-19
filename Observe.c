#include "Header.h"

long currentGyro, startingGyro;

task observeLine(){
	while(currentState != FOLLOWLINE){}
	long gyroPosition = getGyroDegrees(S1);
	clearTimer(T2);
	int longestStraightTime = 0;
	resetGyro(S1);
	startingGyro = abs(getGyroDegrees(S1));
	while(1){
		if(currentState == FOLLOWLINE){
			currentGyro = (abs(getGyroDegrees(S1)));
			if(abs(currentGyro - startingGyro) > 15){
				startingGyro = currentGyro;
				if (time1(T2) > longestStraightTime) {
					longestStraightTime = time1(T2);
					gyroPosition = currentGyro;
				}
				clearTimer(T2);
			}
			if(currentGyro >= 360){
					currentGyro = (abs(getGyroDegrees(S1)));
					while(currentGyro != gyroPosition + 360){
						currentGyro = (abs(getGyroDegrees(S1)));
					}
					clearTimer(T2);
					while(time1(T2) < (longestStraightTime/2) + 1200){
					}
					currentState = OBSERVELINE;
				}
			}
		}
	}
