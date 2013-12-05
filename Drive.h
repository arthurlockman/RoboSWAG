#ifndef DRIVE_H
#define DRIVE_H

#include "Arduino.h"
#include "Servo.h"

class Drive
{
public:
	Drive(int frontLeftPin, int frontRightPin, int rearLeftPin, int rearRightPin);
	void TankDrive(int rightSpeed, int leftSpeed);
	void ArcadeDrive(int moveValue, int rotateValue);
	void DriveIndividual(int frontLeft, int frontRight, int rearLeft, int rearRight);
private:
	Servo m_frontLeftMotor;
	Servo m_frontRightMotor;
	Servo m_rearLeftMotor;
	Servo m_rearRightMotor;
	
	void PowerMotors(int frontLeftSpeed, int frontRightSpeed,
		int rearLeftSpeed, int rearRightSpeed);
};

#endif
