#include "MQTTPublisher.h"

MQTTPublisher::MQTTPublisher(const char* mqttServer, int mqttPort, const char* mqttUser, const char* mqttPassword)
    : client(espClient), server(mqttServer), port(mqttPort), user(mqttUser), password(mqttPassword) {}

void MQTTPublisher::init() {
    client.setServer(server, port);
}

void MQTTPublisher::reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32_Client", user, password)) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void MQTTPublisher::publishData(int count, String time) {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    String payload = "{\"count\": " + String(count) + ", \"time\": \"" + time + "\"}";
    client.publish("CMTEQ/CountUP", payload.c_str());
}

void MQTTPublisher::loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}
