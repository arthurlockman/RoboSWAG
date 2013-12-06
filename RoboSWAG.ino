#include "Drive.h"
#include "Arduino.h"
#include "Robotmap.h"
#include "LineFollower.h"
#include <PPM.h>

PPM controller(2);
Drive swagDrive(kFrontLeftMotor, kFrontRightMotor, 
	kRearLeftMotor, kRearRightMotor);
LineFollower lineFollower(kLineFollowerLeftPin, 
	kLineFollowerRightPin, kLineFollowerMiddlePin);

void setup()
{

}

void loop()
{

}

/**
 * @brief Track a line.
 * @details Tracks a line on the field to a stopping
 * point. By default, the method executes once and 
 * directs the robot in the correct direction. If
 * the parameter is set to true, then the robot will 
 * drive on the line until it reaches a stopping line.
 * 
 * @param stopOnLine Whether or not to drive until 
 * a stopping line is found. 
 */
void trackLine(boolean stopOnLine = false)
{
	if (stopOnLine)
	{
		int stopTracking = 1;
		while(stopTracking)
		{
			switch (lineFollower.TrackLine()) {
			    case kTrackRight:
			    	swagDrive.TankDrive(10,90);
			    	break;
			    case kTrackLeft:
			    	swagDrive.TankDrive(90,10);
			    	break;
			    case kTrackStraight:
			    	swagDrive.TankDrive(60,60);
			    	break;
			    case kStop:
			    	swagDrive.StopRobot();
			    	stopTracking = 0;
			    	break;
			}
		}
	}
	else
	{
		switch (lineFollower.TrackLine()) {
		    case kTrackRight:
		    	swagDrive.TankDrive(10,90);
		    	break;
		    case kTrackLeft:
		    	swagDrive.TankDrive(90,10);
		    	break;
		    case kTrackStraight:
		    	swagDrive.TankDrive(60,60);
		    	break;
		    case kStop:
		    	swagDrive.StopRobot();
		    	stopTracking = 0;
		    	break;
		}
	}
}

