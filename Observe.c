#include "Header.h"

long currentGyro, startingGyro;

task observeLine(){
	while(currentState != FOLLOWLINE){}
	long gyroPosition = getGyroDegrees(S1);
	clearTimer(T2);
	int longestStraightTime = 0;
	while(!startObserve){}
	resetGyro(S1);
	startingGyro = abs(getGyroDegrees(S1));
	while(!objectAvoided){
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
			displayTextLine(2, "%d", getGyroDegrees(S1));
			if(currentGyro >= 360){
				displayTextLine(1, "finding");
				currentGyro = (abs(getGyroDegrees(S1)));
				while(currentGyro != gyroPosition + 350){
					currentGyro = (abs(getGyroDegrees(S1)));
				}
				clearTimer(T2);
				while(time1(T2) < (longestStraightTime/2)){
				}
				currentState = OBSERVELINE;
			}
		}
		abortTimeslice();
	}
}
