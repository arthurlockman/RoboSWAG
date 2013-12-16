#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include "Robotmap.h"

class Manipulator
{
public:
	Manipulator(int lifterMotorPort, int rollerMotorPort, int potPort);
	void RaiseArm(int angle);
	void Collect();
	void Dispense();
	void StopRollers();
	void StopArm();
private:
	Servo lifterMotor;
	Servo rollerMotor;

	static const float kManipulatorP = 1.0;
	static const float kManipulatorI = 0.00;
	static const float kManipulatorD = 0.01;

	int m_armPotPort;
};

#endif
