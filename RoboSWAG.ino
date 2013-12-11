#include "Robotmap.h"

PPM controller(2);
Drive swagDrive(kFrontLeftMotor, kFrontRightMotor, 
	kRearLeftMotor, kRearRightMotor);
UltrasonicRangefinder ultrasonic(A3);
LineSensor line(A1);

void setup()
{
	Serial.begin(115200);
}

void loop()
{
	autonomous(20);
	teleop(180);
}

/**
 * @brief Autonomous mode.
 * @details Operates the robot in autonomous mode for
 * the specified length of time.
 * 
 * @param timeSeconds The length of time to run
 * autonomous mode for.
 */
void autonomous(unsigned long timeSeconds) 
{
	while(0 == controller.getChannel (1)) {}
	unsigned long time = timeSeconds * 1000;
	unsigned long startTime = millis ();

	while (millis () - startTime <= time) 
	{
		//@TODO: Enter autonomous code.
	}
}

/**
 * @brief Teleoperated mode.
 * @details Operates the robot in teleoperated mode for
 * the specified length of time. Exits the program upon 
 * completion.
 * 
 * @param timeSeconds The length of time to run
 * teleoperated mode for.
 */
void teleop(unsigned long timeSeconds)
{
	unsigned long time = timeSeconds * 1000;
	unsigned long startTime = millis();

	while(millis() - startTime <= time)
	{
		//@TODO: Enter teleop code here.
	}

	exit(0);
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

