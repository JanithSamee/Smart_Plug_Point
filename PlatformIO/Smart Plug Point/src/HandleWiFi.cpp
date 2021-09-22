#include "HandleWiFi.h"
#include "Arduino.h"

HandleWiFi::HandleWiFi(HandleEEPROM eeprom)
{

    WiFi.mode(WIFI_STA);
    WiFi.begin(eeprom.readEEPROM(0).c_str(), eeprom.readEEPROM(26).c_str());
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(1000);
    }
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());
}

IPAddress HandleWiFi::getCurrentIp()
{
    return WiFi.localIP();
}