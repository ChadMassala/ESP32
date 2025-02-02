#ifndef MQTTPUBLISHER_H
#define MQTTPUBLISHER_H

#include <WiFi.h>
#include <PubSubClient.h>

//void mqttConnect(const char* MQTT_HOST, const char* MQTT_PORT, String TOPIC, const char *mqtt_client_id);

class MQTTPublisher {
public:
    MQTTPublisher(const char* mqttServer, int mqttPort, const char* mqttUser, const char* mqttPassword);
    void init();
    void publishData(int count, String time);
    void loop();
private:
    WiFiClient espClient;
    PubSubClient client;
    const char* server;
    int port;
    const char* user;
    const char* password;
    void reconnect();
};

#endif
