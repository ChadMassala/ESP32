#include "main.h"

// OLED display width and height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Define I2C pins for ESP32
#define SDA_PIN 4
#define SCL_PIN 16

// Constructor
DisplayHandler::DisplayHandler() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {}

// Initialize Display
void DisplayHandler::init() {
    Wire.begin(SDA_PIN, SCL_PIN);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.clearDisplay();
    display.display();
}

// Display a Message
void DisplayHandler::showMessage(String title, String message) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 5);
    display.print(title);
    
    display.setTextSize(1);
    display.setCursor(10, 30);
    display.print(message);
    
    display.display();
}

// Show IP & MAC Address
void DisplayHandler::showDeviceInfo(String ip) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(10, 0);
    display.print("CMTEQ");

    display.setTextSize(1);
    display.setCursor(10, 20);
    display.print("IP:" + ip);

    // display.setCursor(10, 35);
    // display.print("MAC:" + mac);

    display.setCursor(10, 35);
    display.print("Time:");

    display.display();
}

// Update Time on OLED
void DisplayHandler::updateTime(String time) {
    display.fillRect(40, 35, 78, 10, SSD1306_BLACK); // Clear time area
    display.setCursor(40, 35);
    display.print(time);
    display.display();
}


// Count UP on OLED
void DisplayHandler::CountUP(int count) {
    display.fillRect(10, 50, 110, 10, SSD1306_BLACK); // Clear previous count
    display.setTextSize(1);
    display.setCursor(10, 50);
    display.print("Counter: ");
    display.print(count);
    display.display();
}
