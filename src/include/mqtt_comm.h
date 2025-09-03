#ifndef MQTT_COMM_H
#define MQTT_COMM_H

#include <stdint.h>   // para uint8_t
#include <stddef.h>   // para size_t

extern char ultima_mensagem_recebida[256];

void mqtt_setup(const char *client_id, const char *broker_ip, const char *user, const char *pass);
void mqtt_comm_publish(const char *topic, const uint8_t *data, size_t len);
void mqtt_comm_subscribe(const char* topic);
void mqqt_publish_sensor_data(float temperature, float pressure, float humidity, float lux);
#endif