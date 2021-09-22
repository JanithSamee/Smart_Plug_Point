/*
This class is to get values of readings of sensors
    Sensors- ACS712 Current Sensor
            ZMPT101B Voltage Sensor
    
*/

#include "Arduino.h"

class Measurement
{
public:
    Measurement(int pinVin, int pinIin);
    float getCurrentValue();
    float getVoltageValue();
    float getPowerValue(float v, float i);

private:
    int currentSensorSensitivity = 100;
    int inputPinOfVoltageSensor;
    int inputPinOfCurrentSensor;
};