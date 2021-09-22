/*
    This class is use to drive a OLED 128x32 display
        -Welcome screen 
        -Initialization screen
        -Error screens 
        -Measurement screen [TODO:]

*/

#include "Arduino.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class SecondaryDisplayDriver
{
public:
    SecondaryDisplayDriver();
    void showWelcome();
    void showInitalizing();
    void showIP(IPAddress ip);
    void showError(String error);
    void showMesurement(float v, float i);
};