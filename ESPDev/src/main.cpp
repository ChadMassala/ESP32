#include "main.h"

// MQTT Broker Details
const char *MQTT_HOST = "192.168.8.105";
const int MQTT_PORT = 1883;
const char *mqtt_user = "Chad";
const char *mqtt_password = "massala";
const char *mqtt_client_id = "cmteqESP";
const char *TOPIC = "CMTEQ/CountUP/";

WiFiClient client;
PubSubClient mqttClient(client);

// NTP Configuration
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7200, 60000); // UTC time, updates every 60 sec

// Initialize OLED Display Handler
unsigned long lastUpdate = 0;
int value = 0;
DisplayHandler displayHandler;
MQTTPublisher mqttPublisher(MQTT_HOST, MQTT_PORT, mqtt_user, mqtt_password);
void callback(char *topic, byte *payload, unsigned int length);
void mqttConnect();

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
  timeClient.begin();
  mqttConnect();

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
  // mqttPublisher.loop();
  //  Ensure MQTT is connected
  if (!mqttClient.connected())
  {
    Serial.println("MQTT connection lost, reconnecting...");
    mqttConnect();
  }
  mqttClient.loop();
  String formattedTime = timeClient.getFormattedTime();
  displayHandler.updateTime(formattedTime);

  // Nothing to do here, as the display remains static
  // Update Count Every 1 Second
  if (millis() - lastUpdate >= 1000)
  {
    lastUpdate = millis();
    value++;
    displayHandler.CountUP(value);
    // mqttPublisher.publishData(value, formattedTime);
    mqttClient.publish("CMTEQ/ESP-HUB/TimeUP", String(value).c_str());
  }
}

//======================================================
//
//   M Q T T   C O N N E C T
//
//======================================================
void mqttConnect()
{
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  // mqttClient.setCallback(callback);
  int retryCount = 0;

  while (!client.connected() && retryCount < 5)
  { // Retry 5 times
    Serial.println("Attempting to connect to MQTT broker...");
    if (mqttClient.connect(mqtt_client_id))
    {
      Serial.println("Connected to MQTT broker");
      mqttClient.subscribe(TOPIC);
      return;
    }
    else
    {
      Serial.println("Failed with state ");
      Serial.println(mqttClient.state());
      retryCount++;
      delay(2000);
    }
  }
  if (!mqttClient.connected())
  {
    Serial.println("MQTT connection failed after 5 attempts.");
  }
}

//======================================================
//
//   C A L L  B A C K
//
//======================================================
void callback(char *topic, byte *payload, unsigned int length)
{
  if (length >= 50)
  { // Check for oversized payload
    Serial.println("Payload too large, ignoring");
    return;
  }
  payload[length] = '\0'; // Null-terminate payload
  String strTopic = String(topic);
  String value = String((char *)payload);

  Serial.println(strTopic + ": " + value);
}
