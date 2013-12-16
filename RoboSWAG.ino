#include "Robotmap.h"

PPM controller(2);
// UltrasonicRangefinder ultrasonic(A3);
// LineSensor line(A1);

Servo m_frontLeftMotor;
Servo m_frontRightMotor;
Servo m_rearLeftMotor;
Servo m_rearRightMotor;

void setup()
{
	Serial.begin(115200);
	m_frontLeftMotor.attach(kFrontLeftMotor);
	m_frontRightMotor.attach(kFrontRightMotor);
	m_rearLeftMotor.attach(kRearLeftMotor);
	m_rearRightMotor.attach(kRearRightMotor);
}

void loop()
{
	//autonomous(20);
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
		ArcadeDrive(controller);
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
void trackLine(LineFollower lineFollower, boolean stopOnLine = false)
{
	int stopTracking = 1;
	if (stopOnLine)
	{
		while(stopTracking)
		{
			switch (lineFollower.TrackLine()) {
			    case kTrackRight:
			    	TankDrive(10,90);
			    	break;
			    case kTrackLeft:
			    	TankDrive(90,10);
			    	break;
			    case kTrackStraight:
			    	TankDrive(60,60);
			    	break;
			    case kStop:
			    	StopRobot();
			    	stopTracking = 0;
			    	break;
			}
		}
	}
	else
	{
		switch (lineFollower.TrackLine()) {
		    case kTrackRight:
		    	TankDrive(10,90);
		    	break;
		    case kTrackLeft:
		    	TankDrive(90,10);
		    	break;
		    case kTrackStraight:
		    	TankDrive(60,60);
		    	break;
		    case kStop:
		    	StopRobot();
		    	stopTracking = 0;
		    	break;
		}
	}
}

/**
 * @brief Drive robot in a straight line.
 * @details Drive the robot in a straight line towards
 * an object. This requires that the ultrasonic sensors 
 * are actually within range of a solid object.
 * 
 * @param left The left ultraonsic sensor.
 * @param right The right ultrasonic sensor.
 * @param speed The speed to drive forward at. (-90 to 90).
 */
void driveStraight(UltrasonicRangefinder left, UltrasonicRangefinder right, int speed)
{
	int leftVal = left.GetDistanceInCM();
	int rightVal = right.GetDistanceInCM();
	if(leftVal > rightVal) { TankDrive(speed, speed + 20); }
	else if (rightVal > leftVal) { TankDrive(speed + 20, speed); }
	else if (rightVal == leftVal) { TankDrive(speed, speed); }
}

/**
 * @brief Drives the robot using tank drive.
 * @details Drives the robot using the standard
 * tank drive method, but takes in a PPM object
 * to drive based on the input from a Vex 
 * controller.
 * 
 * @param ppm The PPM object to read joysticks from.
 */
void TankDrive(PPM &ppm)
{
	int leftVal = map(constrain((ppm.getChannel(kLeftStickY) - 90), -75, 75), -75, 75, -90, 90);
	int rightVal = map(constrain((ppm.getChannel(kRightStickY) - 90), -75, 75), -75, 75, -90, 90);
	PowerMotors(leftVal, rightVal, leftVal, rightVal);
}

/**
 * @brief Drives the robot using tank drive.
 * @details Drives the robot using the standard
 * tank drive method, taking in a value for the
 * speed of the right side and the speed of the
 * left side.
 * 
 * @param rightSpeed The speed to drive the right
 * side (-90 to 90).
 * @param leftSpeed The speed to drive the left
 * side (-90 to 90).
 */
void TankDrive(int rightSpeed, int leftSpeed)
{
	PowerMotors(leftSpeed, rightSpeed, leftSpeed, rightSpeed);
}

/**
 * @brief Drives the robot using arcade drive.
 * @details Drives the robot using the standard
 * arcade drive method, but takes in a PPM object
 * to drive based on the input from a Vex 
 * controller.
 * 
 * @param ppm The PPM object to read joysticks from.
 */
void ArcadeDrive(PPM &ppm)
{
	int moveVal = map(constrain((ppm.getChannel(kLeftStickY) - 90), -75, 75), -75, 75, -90, 90);
	int rotateVal = map(constrain((ppm.getChannel(kLeftStickX) - 90), -75, 75), -75, 75, -90, 90);
	ArcadeDrive(moveVal, rotateVal);
}

/**
 * @brief Drives the robot using arcade drive.
 * @details Drives the robot using the standard 
 * arcade drive method. Takes in a value for the 
 * speed of forward motion, and a value for the
 * robot rotation speed.
 * 
 * @param moveValue Forward motion speed (-90 to 90).
 * @param rotateValue Rotation speed (-90 to 90).
 */
void ArcadeDrive(int moveValue, int rotateValue)
{
	int leftSpeed = moveValue; 
	int rightSpeed = moveValue;

	leftSpeed += rotateValue;
	rightSpeed -= rotateValue;

	PowerMotors(leftSpeed, rightSpeed, leftSpeed, rightSpeed);
}

/**
 * @brief Drive wheels individually.
 * @details Drive the drive wheels individually.
 * All values should be input in the range -90 to 90.
 * 
 * @param frontLeft The speed of the front left wheel.
 * @param frontRight The speed of the front right wheel.
 * @param rearLeft The speed of the rear left wheel.
 * @param rearRight The speed of the rear right wheel.
 */
void DriveIndividual(int frontLeft, int frontRight, 
		int rearLeft, int rearRight)
{
	PowerMotors(frontLeft, frontRight, rearLeft, rearRight);
}

/**
 * @brief Stops the robot.
 * @details Stops all forward or reverse motion in
 * the robot.
 */
void StopRobot()
{
	PowerMotors(0, 0, 0, 0);
}

/**
 * @brief Power the motors.
 * @details This method actually drives the motors.
 * This is the only method that should be used for actually
 * interfacing with the motors. The method does math
 * such that the motors will all drive in the same 
 * direction if given the same values.
 * 
 * @param frontLeftSpeed The speed of the front left wheel.
 * @param frontRightSpeed The speed of the front right wheel.
 * @param rearLeftSpeed The speed of the rear left wheel.
 * @param rearRightSpeed The speed of the rear right wheel.
 */
void PowerMotors(int frontLeftSpeed, int frontRightSpeed,
		int rearLeftSpeed, int rearRightSpeed)
{
	m_frontLeftMotor.write(frontLeftSpeed + 90);
	m_frontRightMotor.write(90 - frontRightSpeed);
	m_rearLeftMotor.write(rearLeftSpeed + 90);
	m_rearRightMotor.write(90 - rearRightSpeed);
}
