#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "LineSensor.h"

///Which direction to track in.
enum trackingDirection
{
	kTrackStraight = 1, ///<Track straight.
	kTrackRight, ///< Track to the right.
	kTrackLeft, ///< Track to the left.
	kStop ///< Stop tracking.
};

class LineFollower
{
public:
	LineFollower(int threshold, int leftPin, int rightPin, int middlePin);
	trackingDirection TrackLine();
	void Reset();
private:
	trackingDirection m_lastDirection;
	
	LineSensor m_leftSensor;
	LineSensor m_rightSensor;
	LineSensor m_middleSensor;

	static const int kOffLine = 0;
	static const int kOnLine = 1;
};

#endif