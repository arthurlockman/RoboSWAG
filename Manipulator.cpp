#include "Manipulator.h"

Manipulator::Manipulator(int lifterMotorPort, int rollerMotorPort, int potPort):
	m_armPotPort(potPort)
{
	lifterMotor.attach(lifterMotorPort);
	rollerMotor.attach(rollerMotorPort);
}

void Manipulator::RaiseArm(int angle)
{
	//@TODO: Insert code here.
}
