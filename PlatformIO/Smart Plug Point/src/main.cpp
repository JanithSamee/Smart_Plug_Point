#include "Arduino.h"
#include "EEPROM.h"
#include "ESPAsyncWebServer.h"
#include "AsyncTCP.h"
#include "WebSocketsServer.h"
#include "SPIFFS.h"
#include "Ticker.h"

//include custom classes
#include "Measurement.h"
#include "HandleEEPROM.h"
#include "HandleWiFi.h"
#include "LocalWebServer.h"
#include "SecondaryDisplayDriver.h"

//Initialize the classes
Measurement measurement(26, 24);
AsyncWebServer server(80);
WebSocketsServer websockets(81);
Ticker sender;

//set the bulb on off request listner
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{

  switch (type)
  {
  case WStype_DISCONNECTED:
    Serial.printf("[%u] Disconnected!\n", num);
    break;
  case WStype_CONNECTED:
  {
    IPAddress ip = websockets.remoteIP(num);
    Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

    // send message to client
    websockets.sendTXT(num, "Connected from server");
  }
  break;
  case WStype_TEXT:
    String message = String((char *)(payload));

    if (message == "switch|off")
    {
      digitalWrite(2, LOW);
    }

    if (message == "switch|on")
    {
      digitalWrite(2, HIGH);
    }
  }
}

//send current and voltage measurement to server
  void send_data()
{
  String res = "{\"voltage\":";
  float voltage = measurement.getVoltageValue();
  float current = measurement.getCurrentValue();
  res += String(voltage, 2);
  res += ",\"current\":";
  res += String(current, 2);
  res += "}";
  websockets.broadcastTXT(res);
  Serial.println(res);
  
}
void setup()
{
  //initalize input and output pins
  pinMode(2, OUTPUT);

  SecondaryDisplayDriver secondaryDisplayDriver;
  secondaryDisplayDriver.showWelcome();
  delay(1000);
  secondaryDisplayDriver.showInitalizing();

  //initalize the EEPROM of device
  HandleEEPROM handleEEPROM(512);

  //Start the serial port
  Serial.begin(115200);

  //Start WIFI
  HandleWiFi HandleWiFi(handleEEPROM);
  IPAddress myip = HandleWiFi.getCurrentIp();
  secondaryDisplayDriver.showIP(myip);

  delay(1000);

  //Mount SPI flsg file system
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    secondaryDisplayDriver.showError("FS Mount Fail!");
    return;
  }

  //server initialization
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", String()); });

  server.onNotFound([](AsyncWebServerRequest *request)
                    { request->send(404, "text/html", "<h1>NotFound</h1>"); });
  server.begin();
  websockets.begin();
  websockets.onEvent(webSocketEvent);

  sender.attach(1, send_data);
}

void loop()
{

  websockets.loop();
}