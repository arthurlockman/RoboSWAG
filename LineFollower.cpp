#include "Arduino.h"
#include "LineFollower.h"

/**
 * @brief Constructs the line follower object.
 * @details This method constructs the line follower object. 
 *  
 * @param leftPin The pin that the leftmost sensor is on.
 * @param rightPin The pin that the rightmost sensor is on.
 */
LineFollower::LineFollower(int threshold, int leftPin, int rightPin) :
	m_leftSensor(leftPin, threshold),
	m_rightSensor(rightPin, threshold)
{

}

/**
 * @brief Track a line.
 * @details Returns the direction that the robot should track
 * based on the line sensor input.
 * 
 * @return The direction that the robot should track in. 
 */
trackingDirection LineFollower::TrackLine()
{
	int leftVal = m_leftSensor.Read();
	int rightVal = m_rightSensor.Read();

	if (leftVal == kOffLine && rightVal == kOffLine)
	{
		return m_lastDirection;
	}
	else if (leftVal == kOnLine && rightVal == kOffLine)
	{
		m_lastDirection = kTrackLeft;
		return kTrackLeft;
	}
	else if (leftVal == kOffLine && rightVal == kOnLine)
	{
		m_lastDirection = kTrackRight;
		return kTrackRight;
	}
	else if (leftVal == kOnLine && rightVal == kOnLine)
	{
		m_lastDirection = kStop;
		return kStop;
	}
}

/**
 * @brief Reset the line follower.
 * @details Resets the last known direction of the line follower. 
 */
void LineFollower::Reset()
{
	m_lastDirection = kTrackStraight;
}
