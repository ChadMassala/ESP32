#include "main.h"

// NTP Configuration
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7200, 60000); // UTC time, updates every 60 sec

int value = 0;

// Initialize OLED Display Handler
DisplayHandler displayHandler;
unsigned long lastUpdate = 0;

void setup()
{
  Serial.begin(115200);
  // Initialize Display
  displayHandler.init();
  displayHandler.showMessage("CMTEQ", "Connecting WiFi...");

  // Connect to WiFi
  WiFi.begin(WIFI_SSD, WIFI_PASS);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  // Get IP and MAC Address
  String ipAddress = WiFi.localIP().toString();
  String macAddress = WiFi.macAddress();

  Serial.println("IP Address: " + ipAddress);
  Serial.println("MAC Address: " + macAddress);
  delay(1000);

  // Show Details on OLED
  displayHandler.showDeviceInfo(ipAddress);

  // OTA Setup
  ArduinoOTA.setHostname("ESP32-CMTEQ");
  ArduinoOTA.begin();
}

void loop()
{
  ArduinoOTA.handle(); // Check for OTA updates
  timeClient.update(); // Update time from NTP
  String formattedTime = timeClient.getFormattedTime();
  displayHandler.updateTime(formattedTime);
  // Nothing to do here, as the display remains static
  // Update Count Every 1 Second
  if (millis() - lastUpdate >= 1000)
  {
    lastUpdate = millis();
    value++;
    displayHandler.CountUP(value);
  }

  delay(1000);
}
