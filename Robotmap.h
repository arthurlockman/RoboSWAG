#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "LineFollower.h"
#include "UltrasonicRangefinder.h"
#include "PPM.h"
#include "Arduino.h"
#include "LineSensor.h"
#include "Servo.h"
#include "LimitSwitch.h"

#define DEBUG 1

///The different motors that are attached to the robot.
enum Motors
{
	kFrontLeftMotor = 6, ///< The front left motor.
	kFrontRightMotor = 7, ///< The front right motor.
	kRearLeftMotor = 8, ///< The rear left motor.
	kRearRightMotor = 9, ///< The rear right motor.
	kFeederMotor = 10, ///< The arm motor.
	kArmMotor = 11 ///< The feeder motor.
};

///The digital inputs on the robot.
enum DigitalInputs
{
	kLifterLowerLimit = 22,
	kLifterUpperLimit = 23
};

///The Analog inputs on the robot.
enum AnalogInputs
{
	kLineSensorLeft = 1,
	kLineSensorRight = 2,
	kRangefinderLeft = 3,
	kRangefinderRight = 4
};

///The joystick axis on the robot.
enum JoystickAxis
{
	kRightStickX = 1, ///< The right joystick's X axis.
	kRightStickY = 2, ///< The right joystick's Y axis.
	kLeftStickY = 3, ///< The left joystick's Y axis.
	kLeftStickX = 4, ///< The left joystick's X axis.
	kBackLeftButtons = 5, ///< The joystick's back left buttons.
	kBackRightButtons = 6 ///< The joystick's back right buttons.
};

enum AutonomousState
{
	kStart,
	kDriveToCenter,
	kDriveToPose,
	kPOSERobot,
	kDone
};

///Line following thresholds. 
static const int kWhiteLineThreshold = 475;
static const int kColoredLineThreshold = 850;
static const int kPOSEThreshold = 500; //@TODO: Calculate This
static const float kDOTDistance = 13.65; //CM

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

/**
 * @brief Applies a deadband to a number.
 * @details Applies a deadband to a number. Useful
 * for joystick input and motor output.
 * 
 * @param value The value to apply the deadband to.
 * @param deadbandUpper The upper limit of the deadband.
 * @param deadbandLower The lower limit of the deadband.
 * @param deadbandMid The middle value of the deadband.
 * @return Returns the deadbanded value.
 */
template <typename T>
inline T Deadband(T value, T deadbandUpper, T deadbandLower, T deadbandMid)
{
	if (value <= deadbandUpper && value >= deadbandLower)
		return deadbandMid;
	else 
		return value;
};

#endif
