#include "Arduino.h"
#include "Drive.h"

Drive::Drive(int frontLeftPin, int frontRightPin, int rearLeftPin, int rearRightPin)
{
	m_frontLeftMotor.attach(frontLeftPin);
	m_frontRightMotor.attach(frontRightPin);
	m_rearLeftMotor.attach(rearLeftPin);
	m_rearRightMotor.attach(rearRightPin);
}

void Drive::TankDrive(int rightSpeed, int leftSpeed)
{
	this->PowerMotors(leftSpeed, rightSpeed, leftSpeed, rightSpeed);
}

void Drive::ArcadeDrive(int moveValue, int rotateValue)
{
	int leftSpeed, rightSpeed = constrain(moveValue, 0, 90);

	if (rotateValue > 0)
	{
		leftSpeed += abs(rotateValue);
		rightSpeed -= abs(rotateValue);
	}
	else if (rotateValue < 0);
	{
		leftSpeed -= abs(rotateValue);
		rightSpeed -= abs(rotateValue);
	}
	this->PowerMotors(leftSpeed, rightSpeed, leftSpeed, rightSpeed);
}

void Drive::DriveIndividual(int frontLeft, int frontRight, 
		int rearLeft, int rearRight)
{
	PowerMotors(frontLeft, frontRight, rearLeft, rearRight);
}

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
