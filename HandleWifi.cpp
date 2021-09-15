#include "Arduino.h"
#include "HandleWifi.h"
#include "ESP8266WiFi.h"



String connectToWifi(String ssid, String password) {
  String wifiStatus="none";
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  int connectingTime=0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    connectingTime+=500;
    Serial.print(".");
    if(connectingTime>10000){
      wifiStatus ="timeOut";
      Serial.println("Connection Time Out!");
      break;
    }
    
  }
  if (wifiStatus != "timeOut"){
    wifiStatus= WiFi.localIP().toString();
  }
  return wifiStatus;
}
