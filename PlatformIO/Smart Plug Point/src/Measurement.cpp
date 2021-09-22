#include "Arduino.h"
#include "Measurement.h"

Measurement::Measurement(int pinVin, int pinIin)
{
    inputPinOfCurrentSensor = pinIin;
    inputPinOfVoltageSensor = pinVin;
}

float Measurement::getCurrentValue()
{

    float Vpp;
    int readValue;       //value read from the sensor
    int maxValue = 0;    // store max value here
    int minValue = 1024; // store min value here

    //calculate the peak to peak voltage
    for (size_t i = 0; i < 100; i++)
    {
        readValue = analogRead(inputPinOfCurrentSensor);
        if (readValue > maxValue)
        {
            maxValue = readValue;
        }
        if (readValue < minValue)
        {
            minValue = readValue;
        }
    }

     Vpp = ((maxValue - minValue) * 3.3) / 4096.0;
    float VRMS = (Vpp / 2.0) * 0.707;                         //get the corresponding voltage
    float AmpsRMS = (VRMS * 1000) / currentSensorSensitivity; //get the corresponding current
    return AmpsRMS;
}
float Measurement::getVoltageValue()
{
     float Vpp;
    int readValue;       //value read from the sensor
    int maxValue = 0;    // store max value here
    int minValue = 1024; // store min value here

    //calculate the peak to peak voltage
    for (size_t i = 0; i < 100; i++)
    {
        readValue = analogRead(inputPinOfCurrentSensor);
        if (readValue > maxValue)
        {
            maxValue = readValue;
        }
        if (readValue < minValue)
        {
            minValue = readValue;
        }
    }

     Vpp = ((maxValue - minValue) * 3.3) / 4096.0;
    return Vpp*210;
}

float Measurement::getPowerValue(float v, float i)
{
    return (v + i) / (float)1000;
}
