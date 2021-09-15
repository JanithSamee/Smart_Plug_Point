#include "ESP8266WiFi.h"
#include "EEPROM.h"
#include "ESPAsyncWebServer.h"
#include "Ticker.h"
#include "WebSocketsServer.h"



//Custom headers
#include "HandleEEPROM.h"
#include "HandleWifi.h"
#include "SecondDisplay.h"
#include "Measurement.h"

//Initial variables
String hostName;
String wifiSSID;
String wifiPassword;
String wifiResponse;

const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.4/Chart.js"></script>
    <title>Smart Plug Points</title>

    <style>
      * {
        box-sizing: border-box;
      }

      body {
        margin: 0;
        font-family: Helvetica;
        color: #444444;
      }

      .header {
        overflow: hidden;
        background-color: #f1f1f1;
        padding: 20px 10px;
      }

      .header a {
        float: left;
        color: black;
        text-align: center;
        padding: 12px;
        padding-left: 30px;
        padding-right: 30px;
        margin: 5px;
        text-decoration: none;
        font-size: 18px;
        line-height: 25px;
        border-radius: 4px;
      }
      .header button {
        float: left;
        color: black;
        text-align: center;
        padding: 12px;
        padding-left: 30px;
        padding-right: 30px;
        margin: 5px;
        text-decoration: none;
        font-size: 18px;
        line-height: 25px;
        border: none;
        border-radius: 4px;
      }

      .header a.logo {
        font-size: 25px;
        font-weight: bold;
      }

      .header a:hover {
        background-color: #ddd;
        color: black;
      }
      .header button:hover {
        background-color: #ddd;
        color: black;
      }

      .header button.active-on {
        background-color: dodgerblue;
        color: white;
      }
      .header button.active-off {
        background-color: crimson;
        color: white;
      }

      .header-right {
        float: right;
      }

      .measurement {
        margin: 5px;
        font-size: 24px;
        flex: auto;
      }

      .container1 {
        display: flex;
        flex-direction: row;
      }
      .livedetail {
        display: flex;
        flex-direction: column;
        align-items: center;
        margin: 20px;
        width: 40%;
        padding: 10px;
        border: 5px solid dodgerblue;
        border-radius: 8px;
        font-size: 20px;
        font-weight: bold;
        text-align: center;
      }
      .livegraph {
        width: 55%;
        margin: 20px;
        padding: 10px;
      }
      .form-inline {
        display: flex;
        flex-flow: row wrap;
        align-items: center;
        padding-left: 100px;
      }

      .form-inline label {
        margin: 5px 10px 5px 0;
      }

      .form-inline input {
        vertical-align: middle;
        margin: 5px 10px 5px 0;
        padding: 10px;
        background-color: #fff;
        border: 1px solid #ddd;
      }

      .form-inline button {
        padding: 10px 20px;
        background-color: dodgerblue;
        border: 1px solid #ddd;
        color: white;
        cursor: pointer;
      }

      .form-inline button:hover {
        background-color: royalblue;
      }

      @media (max-width: 800px) {
        .form-inline input {
          margin: 10px 0;
        }

        .form-inline {
          flex-direction: column;
          align-items: stretch;
        }
      }

      @media screen and (max-width: 550px) {
        .header a {
          float: none;
          display: block;
          text-align: left;
          align-items: center;
        }

        .header-right {
          float: none;
          align-items: center;
        }
        .container1 {
          display: flex;
          flex-direction: column;
          align-items: center;
        }
      }
    </style>
  </head>
  <body>
    <div class="header">
      <a href="#default" class="logo">Smart Plug point</a>
      <div class="header-right">
        <button id="btnSwitchON" onclick="handleONOFF()">On</button>
        <button id="btnSwitchOFF" onclick="handleONOFF()">Off</button>
      </div>
    </div>

    <div>
      <center>
        <div class="container1">
          <div class="livegraph">
            <canvas id="graphContainer" style="width: 100%; max-width: 600px"></canvas>
          </div>
          <div class="livedetail">
            <div class="measurement" id="voltage">Voltage:</div>
            <div class="measurement" id="current">Current:</div>
            <div class="measurement" id="power">Power:</div>
          </div>
        </div>
        <hr />
        <h1>Settings</h1>

        <form class="form-inline" action="/action_page.php">
          <center>
            <label for="ssid">SSID:</label>
            <input type="text" id="ssid" placeholder="Enter SSID" name="ssid" />
            <label for="pwd">Password:</label>
            <input type="password" id="pwd" placeholder="Enter password" name="pswd" />
            <button type="submit">save</button>
          </center>
        </form>
      </center>
    </div>

    <script>
      let switchStatus = "off"
      function handleONOFF() 
{
        switch (switchStatus)
        {
          case "on":
            document.getElementById("btnSwitchOFF").className = "active-off";
            document.getElementById("btnSwitchON").className = "";
            switchStatus = "off";
            handleswitch(switchStatus);
            break;
          case "off":
            document.getElementById("btnSwitchOFF").className = "";
            document.getElementById("btnSwitchON").className = "active-on";
            switchStatus = "on";
            handleswitch(switchStatus);
            break;

          default:
            document.getElementById("btnSwitchOFF").disabled = true;
            document.getElementById("btnSwitchON").disabled = true;
            break;
        }
      }
      

      
      

     var dataPlot= new Chart("graphContainer", 
      {
        type: "line",
        data: 
        {
          labels: [],
          datasets: [
            {
              fill: false,
              lineTension: 0,
              backgroundColor: "rgba(0,0,255,1.0)",
              borderColor: "rgba(0,0,255,0.1)",
              data: [],
            },
          ],
        },
        options: 
        {
          legend: 
          { 
            display: true 
          },

          scales: 
          {
            yAxes: [
            { 
              ticks: 
              { 
                
                min: 0 },
                scaleLabel: {
        display: true,
        labelString: 'Power(kW)'
      } 
                }],
          },
        },
      })


        function removeData(){
    dataPlot.data.labels.shift();
    dataPlot.data.datasets[0].data.shift();
  }
  function addData(label, data) {
    console.log(data)
    if(dataPlot.data.labels.length > 20) removeData();
    dataPlot.data.labels.push(label);
    dataPlot.data.datasets[0].data.push(data);
    dataPlot.update();
  }
      
      var connection = new WebSocket("ws://" + location.hostname + ":81/")

      function handleswitch(value)
      {
        try 
        {
          connection.send("switch|" + value);
        } 
        catch (error) 
        {
          alert("Faild");
        }
      }
      try
      {
        connection.onmessage = function (event) 
        {
          let data = JSON.parse(event.data);
          document.getElementById("voltage").innerHTML = "Voltage: " + String(data.voltage) + " V";
          document.getElementById("current").innerHTML = "Current: " + String(data.current) + " A";
          document.getElementById("power").innerHTML =
            "Power: " + String(((data.voltage * data.current) / 1000).toFixed(2)) + " kW";

             var today = new Date();
      var t = today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds();
      addData(t, ((data.voltage * data.current) / 1000).toFixed(2));
        }
      }
      catch (error) 
      {
        alert("Faild to load file");
      }
    </script>
  </body>
</html>

)=====";

//inital libraries
 AsyncWebServer server(80);
 WebSocketsServer websockets(81);
 Ticker sender;






//default functions
void send_data() {
String res = "{\"voltage\":";
   float voltage= getVoltageValue();
   float current =getCurrentValue(A0);
   res+= String(voltage,2);
   res+= ",\"current\":";
   res+=String(current,2);
   res+="}";
  websockets.broadcastTXT(res);
  Serial.println(res);
  
  }

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch (type) 
  {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {
        IPAddress ip = websockets.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // send message to client
        websockets.sendTXT(num, "Connected from server");
      }
      break;
    case WStype_TEXT:
      String message = String((char*)( payload));
      

      if(message == "switch|off"){
        digitalWrite(D1,LOW);
      }

      if(message == "switch|on"){
        digitalWrite(D1,HIGH);
      }

  } 
}

void setup() {
  Serial.begin(115200);

  
  
  pinMode(A0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect.
  }

  
  
  //Libraries intialize in setup
  EEPROM.begin(512);
  
  
  
  wifiSSID= readEEPROM(0);
  wifiPassword= readEEPROM(21);
  hostName= readEEPROM(35);
  wifiResponse=connectToWifi(wifiSSID,wifiPassword);

  
  
  server.on("/", [](AsyncWebServerRequest * request) {
    request->send(200, "text/html", index_html);
  });
  server.onNotFound([](AsyncWebServerRequest * request) {
    request->send(404, "text/html", "<h1>NotFound</h1>");
  });

  //Start services
  server.begin();
  websockets.begin();
  websockets.onEvent(webSocketEvent);
  sender.attach(1,send_data);
  

}

void loop() {
 websockets.loop();
}
