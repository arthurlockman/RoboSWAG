#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "LineFollower.h"
#include "UltrasonicRangefinder.h"
#include "PPM.h"
#include "Drive.h"
#include "Arduino.h"
#include "LineSensor.h"
///The different motors that are attached to the robot.
enum Motors
{
	kFrontLeftMotor = 1, ///< The front left motor.
	kFrontRightMotor, ///< The front right motor.
	kRearLeftMotor, ///< The rear left motor.
	kRearRightMotor, ///< The rear right motor.
	kArmMotor, ///< The arm motor.
	kFeederMotor ///< The feeder motor.
};

///The digital inputs on the robot.
enum DigitalInputs
{
	kLineFollowerRightPin = 1, ///< The right pin for the line follower.
	kLineFollowerLeftPin = 2, ///< The left pin for the line follower.
	kLineFollowerMiddlePin = 3 ///< The middle pin for the line follower.
};

///The Analog inputs on the robot.
enum AnalogInputs
{
	kAI1 = A1
};

///The joystick axis on the robot.
enum JoystickAxis
{
	kRightStickX = 1, ///< The right joystick's X axis.
	kRightStickY, ///< The right joystick's Y axis.
	kLeftStickY, ///< The left joystick's Y axis.
	kLeftStickX ///< The left joystick's X axis.
};

#endif
