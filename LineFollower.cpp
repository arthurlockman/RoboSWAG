#include "Arduino.h"
#include "LineFollower.h"

/**
 * @brief Constructs the line follower object.
 * @details This method constructs the line follower object,
 * automatically deciding whether or not to run in two-input
 * mode or three-input mode.
 * 
 * @param leftPin The pin that the leftmost sensor is on.
 * @param rightPin The pin that the rightmost sensor is on.
 * @param middlePin (Optional) The pin that the center sensor is on.
 */
LineFollower::LineFollower(int leftPin, int rightPin, int middlePin) :
	m_leftPin(leftPin),
	m_rightPin(rightPin),
	m_middlePin(middlePin)
{
	if (middlePin != -1)
	{
		pinMode(m_leftPin, INPUT);
		pinMode(m_rightPin, INPUT);
		pinMode(m_middlePin, INPUT);
		m_mode = kThreeTrackers;
	}
	else
	{
		pinMode(leftPin, INPUT);
		pinMode(rightPin, INPUT);
		m_mode = kTwoTrackers;
	}
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
	int leftVal = digitalRead(m_leftPin);
	int rightVal = digitalRead(m_rightPin);
	int midVal = 0;
	if (m_mode == kThreeTrackers) {midVal = digitalRead(m_middlePin);}
	switch (m_mode) 
	{
		case kTwoTrackers:
			if (leftVal == kOffLine && rightVal == kOffLine)
			{
				m_lastDirection = kTrackStraight;
				return kTrackStraight;
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
			break;
		case kThreeTrackers:

			break;
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
