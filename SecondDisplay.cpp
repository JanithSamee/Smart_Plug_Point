#include "Arduino.h"
#include "SecondDisplay.h"
//
//
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
//
//#define SCREEN_WIDTH 128 
//#define SCREEN_HEIGHT 32
//#define OLED_RESET     -1 
//#define SCREEN_ADDRESS 0x3C 
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//
//void initDisplay(){
//   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
//    Serial.println(F("SSD1306 allocation failed"));
//    for(;;);
//  }
//  delay(2000);
//  display.clearDisplay();
//
//  display.setTextSize(1.2);
//  display.setTextColor(WHITE);
//  }
//
//void showMeasurement(float current,float voltage){
//  // Display static text
//  display.setCursor(0, 3);
//  display.println("Current: "+String(current,2)+" A");
//  display.println("Voltage: "+ String(voltage,2)+" V");
//  float power= (current*voltage)/(float)1000;
//  display.println("Power: "+String(power,3) +" kW");
//  display.display();
//  display.clearDisplay();
//  }
