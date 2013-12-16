#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "LineFollower.h"
#include "UltrasonicRangefinder.h"
#include "PPM.h"
#include "Arduino.h"
#include "LineSensor.h"
#include "Servo.h"
///The different motors that are attached to the robot.
enum Motors
{
	kFrontLeftMotor = 6, ///< The front left motor.
	kFrontRightMotor = 7, ///< The front right motor.
	kRearLeftMotor = 8, ///< The rear left motor.
	kRearRightMotor = 9, ///< The rear right motor.
	kArmMotor = 10, ///< The arm motor.
	kFeederMotor = 11 ///< The feeder motor.
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
	kRightStickY = 2, ///< The right joystick's Y axis.
	kLeftStickY = 3, ///< The left joystick's Y axis.
	kLeftStickX = 4 ///< The left joystick's X axis.
};

/**
 * @brief Tells whether or not a value is within a certain tolerance of another value.
 * @param value The value to check.
 * @param desiredValue The value to check value against.
 * @param tolerance The desired tolerance.
 * @return A boolean, whether or not the value is within the tolerance.
 */
template <typename T>
inline bool WithinTolerance(T value, T desiredValue, T tolerance)
{
	if ((value < desiredValue + tolerance) && (value > desiredValue - tolerance))
    	return true;
	else
    	return false;
};

#endif
