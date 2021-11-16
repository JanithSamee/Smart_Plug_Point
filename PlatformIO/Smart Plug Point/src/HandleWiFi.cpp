#include "HandleWiFi.h"
#include "Arduino.h"
#include "HandleEEPROM.h"

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

int HandleWiFi::changeCredentials(String ssid, String password, HandleEEPROM eeprom)
{
    bool res1 = eeprom.writeEEPROM(0, ssid);
    delay(200);
    bool res2 = eeprom.writeEEPROM(26, password);
    if (res1 && res2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
