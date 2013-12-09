#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include "Robotmap.h"

class Manipulator
{
public:
	Manipulator(int lifterMotorPort, int rollerMotorPort, int potPort);
	void RaiseArm(int angle);
private:
	Servo lifterMotor;
	Servo rollerMotor;

	int m_armPotPort;
};

#endif