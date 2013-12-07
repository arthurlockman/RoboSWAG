#ifndef LINESENSOR_H
#define LINESENSOR_H

class LineSensor
{
public:
	LineSensor(int pin, int threshold = 512);
	int Read();
	int RawRead();
	void SetThreshold(int threshold);
	void AutoThreshold(int bright, int dark);
private:
	int m_threshold;
	int m_sensorPin;
};

#endif
