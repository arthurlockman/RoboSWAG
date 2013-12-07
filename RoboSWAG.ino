#include "Drive.h"
#include "Arduino.h"
#include "Robotmap.h"
#include "LineFollower.h"
#include "UltrasonicRangefinder.h"
#include "PPM.h"

PPM controller(2);
Drive swagDrive(kFrontLeftMotor, kFrontRightMotor, 
	kRearLeftMotor, kRearRightMotor);
UltrasonicRangefinder ultrasonic(A3);

void setup()
{
	Serial.begin(115200);
}

void loop()
{
	Serial.println(ultrasonic.GetDistanceInInches());
	delay(500);
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
void trackLine(LineFollower lineFollower, Drive robotDrive, boolean stopOnLine = false)
{
	int stopTracking = 1;
	if (stopOnLine)
	{
		while(stopTracking)
		{
			switch (lineFollower.TrackLine()) {
			    case kTrackRight:
			    	robotDrive.TankDrive(10,90);
			    	break;
			    case kTrackLeft:
			    	robotDrive.TankDrive(90,10);
			    	break;
			    case kTrackStraight:
			    	robotDrive.TankDrive(60,60);
			    	break;
			    case kStop:
			    	robotDrive.StopRobot();
			    	stopTracking = 0;
			    	break;
			}
		}
	}
	else
	{
		switch (lineFollower.TrackLine()) {
		    case kTrackRight:
		    	robotDrive.TankDrive(10,90);
		    	break;
		    case kTrackLeft:
		    	robotDrive.TankDrive(90,10);
		    	break;
		    case kTrackStraight:
		    	robotDrive.TankDrive(60,60);
		    	break;
		    case kStop:
		    	robotDrive.StopRobot();
		    	stopTracking = 0;
		    	break;
		}
	}
}

