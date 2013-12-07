#include "LineSensor.h"
#include "Arduino.h"

LineSensor::LineSensor(int pin, int threshold) :
	m_sensorPin(pin),
	m_threshold(threshold)
{
	//Done.
}

/**
 * @brief Read the line sensor.
 * @details Read the sensor. Returns 1
 * when on a line (under the threshold) and 
 * returns 0 when off a line.
 * 
 * @return Returns 0 when off a line, 1 when on.
 */
int LineSensor::Read()
{
	int val = analogRead(m_sensorPin);
	if (val >= m_threshold)
		return 0;
	else
		return 1;
}

/**
 * @brief Read the raw values from the sensor.
 * @details Read the raw analog values from the 
 * line sensor. Useful for calibration.
 * 
 * @return The sensor value, an int from 0-1023.
 */
int LineSensor::RawRead()
{
	return analogRead(m_sensorPin);
}

/**
 * @brief Sets the sensor threshold.
 * @details Set the threshold at which the 
 * sensor flips from on to off. Any values
 * outside of the range 0-1023 will be 
 * constrained to the min or max of that 
 * range.
 * 
 * @param threshold The new threshold to use.
 */
void LineSensor::SetThreshold(int threshold)
{
	m_threshold = constrain(threshold, 0, 1023);
}

/**
 * @brief Automatically calculate threshold given
 * values for bright and dark.
 * @details This method automatically calculates
 * the threshold based on measured reflectance values
 * for light and dark from the sensor.
 * 
 * @param bright The sensor reading at bright (on).
 * @param dark The sensor reading at dark (off).
 */
void LineSensor::AutoThreshold(int bright, int dark)
{
	int threshold = ((dark - bright) / 2) + bright;
	this->SetThreshold(threshold);
}
