/*
    This Class is used to handle wifi clients.
        Initally we get the wifi credentials from EEPROM and try to connect

*/

#include "Arduino.h"
#include "WiFi.h"
#include "HandleEEPROM.h"
class HandleWiFi
{
public:
    HandleWiFi(HandleEEPROM eeprom);
    IPAddress getCurrentIp();

private:
    String APSSID = "Smart Plug Point";
    String APPW = "12345678";
};