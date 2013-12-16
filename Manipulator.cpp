#include "Manipulator.h"

Manipulator::Manipulator(int lifterMotorPort, int rollerMotorPort, int potPort):
	m_armPotPort(potPort)
{
	lifterMotor.attach(lifterMotorPort);
	rollerMotor.attach(rollerMotorPort);
}

void Manipulator::RaiseArm(int angle)
{
	int error = 0;
  	int iError = 0;
  	int prevError = 0;
  	int dError = 0;
	int onTarget = 0;
	while (!onTarget)
	{
		int raw = analogRead(m_armPotPort);
		int measuredPos = map(raw, 0, 1023, 0, 180);
		error = angle - measuredPos;
    	iError += error;
    	dError += error - prevError;
    	prevError = error;
    	int pOut = int((kManipulatorP * error) + (kManipulatorI * iError) + (kManipulatorD * dError));
    	lifterMotor.write(90 + pOut);
    	if (WithinTolerance(measuredPos, angle, 2)) { onTarget = 1; }
	}
	StopArm();
}

void Manipulator::Collect()
{
	//@TODO: Insert code here.
}

void Manipulator::Dispense()
{
	//@TODO: Insert code here.
}

void Manipulator::StopRollers()
{
	rollerMotor.write(90);
}

void Manipulator::StopArm()
{
	lifterMotor.write(90);
	rollerMotor.write(90);
}
