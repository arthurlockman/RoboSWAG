#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

///Which mode the sensor will operate in.
enum trackingMode
{
	kTwoTrackers = 1, ///< Operate with two line trackers.
	kThreeTrackers ///< Operate with three line trackers.
};

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
	LineFollower(int leftPin, int rightPin, int middlePin = 0);
	trackingDirection TrackLine();
	void Reset();
private:
	trackingMode m_mode;
	trackingDirection m_lastDirection;
	
	int m_leftPin;
	int m_rightPin;
	int m_middlePin;

	static const int kOffLine = 1;
	static const int kOnLine = 0;
};

#endif