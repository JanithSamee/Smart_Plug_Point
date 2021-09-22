#include "secondaryDisplayDriver.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SecondaryDisplayDriver::SecondaryDisplayDriver()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
    delay(1000);
    display.clearDisplay();

    display.setTextSize(1.2);
    display.setTextColor(WHITE);
}

void SecondaryDisplayDriver::showWelcome()
{
    display.clearDisplay();
    display.setCursor(2, 12);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("WELCOME");
    display.display();
}

void SecondaryDisplayDriver::showInitalizing()
{
    display.clearDisplay();
    display.setCursor(2, 12);
    display.setTextSize(1.7);
    display.setTextColor(WHITE);
    display.print("Initializing...");
    display.display();
}

void SecondaryDisplayDriver::showIP(IPAddress ip)
{
    display.clearDisplay();
    display.setCursor(2, 5);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Webpage IP Address: ");
    display.println(ip);
    display.display();
}

void SecondaryDisplayDriver::showError(String error)
{
    display.clearDisplay();
    display.setCursor(2, 12);
    display.setTextSize(1.7);
    display.setTextColor(WHITE);
    display.print(error);
    display.display();
}

void SecondaryDisplayDriver::showMesurement(float v, float i)
{
    display.clearDisplay();
    display.setCursor(2, 2);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print("Volatge: ");
    display.print(v);
    display.print(" V");
    display.print("Current: ");
    display.print(i);
    display.print(" A");
    display.print("Power: ");
    display.print(String((v * i) / (float)1000, 2));
    display.print(" kW");

    display.display();
}