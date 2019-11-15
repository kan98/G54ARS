#include "Header.h"
#include "FindLine.c"
#include "FollowLine.c"
#include "Avoid.c"


task arbiterTask() {

	while (1) {
		switch(currentState) {
			case AVOIDLINE:
				setMotorSpeed(motorA, leftMotorSpeedAvoid);
				setMotorSpeed(motorC, rightMotorSpeedAvoid);
				break;
			case FOLLOWLINE:
				setMotorSpeed(motorA, leftMotorSpeedFollow);
				setMotorSpeed(motorC, rightMotorSpeedFollow);
				break;
			case FINDINGLINE:
			default:
				setMotorSpeed(motorA, leftMotorSpeedFind);
				setMotorSpeed(motorC, rightMotorSpeedFind);
				break;
		}
		abortTimeslice();
	}
}

task main()
{
	startTask(findLine);
	startTask(followLine);
	startTask(avoidLine);
	startTask(arbiterTask);
	while(1){}
}
