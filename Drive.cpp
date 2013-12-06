#include "Arduino.h"
#include "Drive.h"

/**
 * @brief Constructs the robot drive object.
 * @details This method attaches all of the 
 * servo motors to their proper pins, and 
 * finishes construction of the drive object.
 * 
 * @param frontLeftPin The pin that the front left
 * motor is on.
 * @param frontRightPin The pin that the front right
 * motor is on.
 * @param rearLeftPin The pin that the rear left 
 * motor is on.
 * @param rearRightPin The pin that the rear right
 * motor is on.
 * @return Constructor, returns void.
 */
Drive::Drive(int frontLeftPin, int frontRightPin, 
	int rearLeftPin, int rearRightPin)
{
	m_frontLeftMotor.attach(frontLeftPin);
	m_frontRightMotor.attach(frontRightPin);
	m_rearLeftMotor.attach(rearLeftPin);
	m_rearRightMotor.attach(rearRightPin);
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
void Drive::TankDrive(PPM &ppm)
{
	this->TankDrive(map(ppm.getChannel(kLeftStickY), 0, 180, -90, 90), 
		map(ppm.getChannel(kRightStickY), 0, 180, -90, 90));
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
void Drive::TankDrive(int rightSpeed, int leftSpeed)
{
	this->PowerMotors(leftSpeed, rightSpeed, leftSpeed, rightSpeed);
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
void Drive::ArcadeDrive(PPM &ppm)
{
	this->ArcadeDrive(map(ppm.getChannel(kLeftStickY), 0, 180, -90, 90), 
		map(ppm.getChannel(kRightStickX), 0, 180, -90, 90));
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
void Drive::ArcadeDrive(int moveValue, int rotateValue)
{
	int leftSpeed, rightSpeed = constrain(moveValue, -90, 90);

	if (rotateValue > 0)
	{
		leftSpeed += abs(rotateValue);
		rightSpeed -= abs(rotateValue);
	}
	else if (rotateValue < 0);
	{
		leftSpeed -= abs(rotateValue);
		rightSpeed += abs(rotateValue);
	}
	this->PowerMotors(leftSpeed, rightSpeed, leftSpeed, rightSpeed);
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
void Drive::DriveIndividual(int frontLeft, int frontRight, 
		int rearLeft, int rearRight)
{
	PowerMotors(frontLeft, frontRight, rearLeft, rearRight);
}

/**
 * @brief Stops the robot.
 * @details Stops all forward or reverse motion in
 * the robot.
 */
void Drive::StopRobot()
{
	this->PowerMotors(0, 0, 0, 0);
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
void Drive::PowerMotors(int frontLeftSpeed, int frontRightSpeed,
		int rearLeftSpeed, int rearRightSpeed)
{
	frontLeftSpeed = constrain(frontLeftSpeed, 0, 90);
	frontLeftSpeed = constrain(frontRightSpeed, 0, 90);
	rearLeftSpeed = constrain(rearLeftSpeed, 0, 90);
	rearRightSpeed = constrain(rearRightSpeed, 0, 90);
	//@TODO: Check this.
	m_frontLeftMotor.write(90 - frontLeftSpeed);
	m_frontRightMotor.write(90 + frontRightSpeed);
	m_rearLeftMotor.write(90 - rearLeftSpeed);
	m_rearRightMotor.write(90 + rearRightSpeed);
}
